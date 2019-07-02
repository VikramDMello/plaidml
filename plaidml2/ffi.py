# Copyright 2019 Intel Corporation.

import os
import platform
import sys
import threading

import pkg_resources

from plaidml2._ffi import ffi

_TLS = threading.local()
_TLS.err = ffi.new('plaidml_error*')


def __load_library():
    native_path = os.getenv('PLAIDML_NATIVE_PATH')
    if native_path:
        return ffi.dlopen(native_path)

    if platform.system() == 'Windows':
        lib_name = 'plaidml.dll'
    elif platform.system() == 'Darwin':
        lib_name = 'libplaidml.dylib'
    else:
        lib_name = 'libplaidml.so'

    lib_path = pkg_resources.resource_filename(__name__, lib_name)
    return ffi.dlopen(lib_path)


lib = ffi.init_once(__load_library, 'plaidml_load_library')


def decode_str(ptr):
    if ptr:
        try:
            return ffi.string(lib.plaidml_string_ptr(ptr)).decode()
        finally:
            lib.plaidml_string_free(ptr)
    return None


class Error(Exception):

    def __init__(self, err):
        Exception.__init__(self)
        self.code = err.code
        self.msg = decode_str(err.msg)

    def __str__(self):
        return self.msg


def ffi_call(func, *args):
    """Calls ffi function and propagates foreign errors."""
    ret = func(_TLS.err, *args)
    if _TLS.err.code:
        raise Error(_TLS.err)
    return ret


def __init():
    ffi_call(lib.plaidml_init)


ffi.init_once(__init, 'plaidml_init')


class ForeignObject(object):
    __ffi_obj__ = None
    __ffi_del__ = None
    __ffi_repr__ = None

    def __init__(self, ffi_obj):
        self.__ffi_obj__ = ffi_obj

    def __del__(self):
        if self.__ffi_obj__ and self.__ffi_del__:
            self._methodcall(self.__ffi_del__)

    def __repr__(self):
        if self.__ffi_obj__ is None:
            return 'None'
        if self.__ffi_obj__ and self.__ffi_repr__:
            return decode_str(self._methodcall(self.__ffi_repr__))
        return super(ForeignObject, self).__repr__()

    def _methodcall(self, func, *args):
        return ffi_call(func, self.__ffi_obj__, *args)

    def as_ptr(self, release=False):
        if self.__ffi_obj__ is None:
            return ffi.NULL
        ret = self.__ffi_obj__
        if release:
            self.__ffi_obj__ = None
        return ret

    def set_ptr(self, ffi_obj):
        self.__ffi_obj__ = ffi_obj

    def take_ptr(self, obj):
        self.__ffi_obj__ = obj.as_ptr(True)