// Copyright 2019 Intel Corporation.

#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef PLAIDML_EDSL_DLL
#define PLAIDML_EDSL_API __declspec(dllexport)
#else
#define PLAIDML_EDSL_API __declspec(dllimport)
#endif
#elif __GNUC__ >= 4
#define PLAIDML_EDSL_API __attribute__((visibility("default")))
#else
#define PLAIDML_EDSL_API
#endif

#include "plaidml2/core/ffi.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef enum {
  PLAIDML_INT_OP_NEG,
  PLAIDML_INT_OP_ADD,
  PLAIDML_INT_OP_SUB,
  PLAIDML_INT_OP_MUL,
  PLAIDML_INT_OP_DIV,
} plaidml_int_op;

PLAIDML_EDSL_API plaidml_logical_shape* plaidml_logical_shape_alloc(  //
    plaidml_error* err,                                               //
    plaidml_datatype dtype,                                           //
    size_t ndims,                                                     //
    const int64_t* dims);

PLAIDML_EDSL_API void plaidml_logical_shape_free(  //
    plaidml_error* err,                            //
    plaidml_logical_shape* shape);

PLAIDML_EDSL_API plaidml_string* plaidml_logical_shape_repr(  //
    plaidml_error* err,                                       //
    plaidml_logical_shape* shape);

PLAIDML_EDSL_API size_t plaidml_logical_shape_get_ndims(  //
    plaidml_error* err,                                   //
    plaidml_logical_shape* shape);

PLAIDML_EDSL_API plaidml_datatype plaidml_logical_shape_get_dtype(  //
    plaidml_error* err,                                             //
    plaidml_logical_shape* shape);

PLAIDML_EDSL_API int64_t plaidml_logical_shape_get_dim_int(  //
    plaidml_error* err,                                      //
    plaidml_logical_shape* shape,                            //
    size_t dim);

PLAIDML_EDSL_API plaidml_dim_expr* plaidml_logical_shape_get_dim_expr(  //
    plaidml_error* err,                                                 //
    plaidml_logical_shape* shape,                                       //
    size_t dim);

PLAIDML_EDSL_API void plaidml_poly_expr_free(  //
    plaidml_error* err,                        //
    plaidml_poly_expr* expr);

PLAIDML_EDSL_API plaidml_string* plaidml_poly_expr_repr(  //
    plaidml_error* err,                                   //
    plaidml_poly_expr* expr);

PLAIDML_EDSL_API plaidml_poly_expr* plaidml_poly_expr_dim(  //
    plaidml_error* err,                                     //
    plaidml_dim_expr* expr);

PLAIDML_EDSL_API plaidml_poly_expr* plaidml_poly_expr_index(  //
    plaidml_error* err,                                       //
    const char* name);

PLAIDML_EDSL_API plaidml_poly_expr* plaidml_poly_expr_literal(  //
    plaidml_error* err,                                         //
    int64_t value);

PLAIDML_EDSL_API plaidml_poly_expr* plaidml_poly_expr_op(  //
    plaidml_error* err,                                    //
    plaidml_int_op op,                                     //
    size_t nargs,                                          //
    plaidml_poly_expr** args);

PLAIDML_EDSL_API void plaidml_poly_expr_add_constraint(  //
    plaidml_error* err,                                  //
    plaidml_poly_expr* lhs,                              //
    plaidml_dim_expr* rhs);

PLAIDML_EDSL_API void plaidml_dim_expr_free(  //
    plaidml_error* err,                       //
    plaidml_dim_expr* expr);

PLAIDML_EDSL_API plaidml_string* plaidml_dim_expr_repr(  //
    plaidml_error* err,                                  //
    plaidml_dim_expr* expr);

PLAIDML_EDSL_API plaidml_dim_expr* plaidml_dim_expr_none(  //
    plaidml_error* err                                     //
);

PLAIDML_EDSL_API plaidml_dim_expr* plaidml_dim_expr_ref(  //
    plaidml_error* err,                                   //
    plaidml_expr* ref,                                    //
    size_t dim);

PLAIDML_EDSL_API plaidml_dim_expr* plaidml_dim_expr_int(  //
    plaidml_error* err,                                   //
    int64_t value);

PLAIDML_EDSL_API int64_t plaidml_dim_expr_get_int(  //
    plaidml_error* err,                             //
    plaidml_dim_expr* expr);

PLAIDML_EDSL_API plaidml_dim_expr* plaidml_dim_expr_op(  //
    plaidml_error* err,                                  //
    plaidml_int_op op,                                   //
    size_t nargs,                                        //
    plaidml_dim_expr** args);

PLAIDML_EDSL_API void plaidml_expr_free(  //
    plaidml_error* err,                   //
    plaidml_expr* expr);

PLAIDML_EDSL_API plaidml_logical_shape* plaidml_expr_get_shape(  //
    plaidml_error* err,                                          //
    plaidml_expr* expr);

PLAIDML_EDSL_API void plaidml_expr_bind_shape(  //
    plaidml_error* err,                         //
    plaidml_expr* expr,                         //
    plaidml_logical_shape* shape);

PLAIDML_EDSL_API void plaidml_expr_bind_dims(  //
    plaidml_error* err,                        //
    plaidml_expr* expr,                        //
    size_t ndims,                              //
    plaidml_dim_expr** dims);

PLAIDML_EDSL_API plaidml_string* plaidml_expr_repr(  //
    plaidml_error* err,                              //
    plaidml_expr* expr);

PLAIDML_EDSL_API plaidml_expr* plaidml_expr_dim(  //
    plaidml_error* err,                           //
    plaidml_dim_expr* expr);

PLAIDML_EDSL_API plaidml_expr* plaidml_expr_param(  //
    plaidml_error* err,                             //
    plaidml_logical_shape* shape,                   //
    const char* name);

PLAIDML_EDSL_API plaidml_expr* plaidml_expr_int(  //
    plaidml_error* err,                           //
    int64_t value);

PLAIDML_EDSL_API int64_t plaidml_expr_int_get_value(  //
    plaidml_error* err,                               //
    plaidml_expr* expr);

PLAIDML_EDSL_API plaidml_expr* plaidml_expr_float(  //
    plaidml_error* err,                             //
    double value);

PLAIDML_EDSL_API double plaidml_expr_float_get_value(  //
    plaidml_error* err,                                //
    plaidml_expr* expr);

PLAIDML_EDSL_API plaidml_expr* plaidml_expr_call(  //
    plaidml_error* err,                            //
    const char* fn,                                //
    size_t nargs,                                  //
    plaidml_expr** args);

PLAIDML_EDSL_API plaidml_expr* plaidml_expr_tensor_spec(  //
    plaidml_error* err,                                   //
    plaidml_expr* ref,                                    //
    size_t ndims,                                         //
    plaidml_poly_expr** input_idxs,                       //
    plaidml_dim_expr** output_sizes);

typedef enum {
  PLAIDML_AGG_OP_NONE,
  PLAIDML_AGG_OP_SUM,
  PLAIDML_AGG_OP_MAX,
  PLAIDML_AGG_OP_MIN,
  PLAIDML_AGG_OP_PROD,
  PLAIDML_AGG_OP_ASSIGN
} plaidml_agg_op;

typedef enum {
  PLAIDML_COMBO_OP_NONE,
  PLAIDML_COMBO_OP_MUL,
  PLAIDML_COMBO_OP_ADD,
  PLAIDML_COMBO_OP_EQ,
  PLAIDML_COMBO_OP_COND,
} plaidml_combo_op;

PLAIDML_EDSL_API plaidml_expr* plaidml_expr_contraction(  //
    plaidml_error* err,                                   //
    plaidml_agg_op agg_op,                                //
    plaidml_combo_op combo_op,                            //
    plaidml_expr* raw_output,                             //
    size_t ninputs,                                       //
    plaidml_expr** raw_inputs,                            //
    const char* name);

PLAIDML_EDSL_API void plaidml_expr_contraction_set_no_defract(  //
    plaidml_error* err,                                         //
    plaidml_expr* expr,                                         //
    bool no_defract);

PLAIDML_EDSL_API void plaidml_expr_contraction_set_use_default(  //
    plaidml_error* err,                                          //
    plaidml_expr* expr,                                          //
    plaidml_expr* use_default);

PLAIDML_EDSL_API void plaidml_program_free(  //
    plaidml_error* err,                      //
    plaidml_program* program);

PLAIDML_EDSL_API plaidml_program* plaidml_program_evaluate(  //
    plaidml_error* err,                                      //
    const char* name,                                        //
    size_t nexprs,                                           //
    plaidml_expr** raw_exprs);

PLAIDML_EDSL_API plaidml_string* plaidml_program_repr(  //
    plaidml_error* err,                                 //
    plaidml_program* program);

// This is a temporary HACK to provide underlying access to the RunInfo
PLAIDML_EDSL_API const void* plaidml_program_runinfo(  //
    plaidml_error* err,                                //
    plaidml_program* program);

// TODO: We can't have this API (which provides support for offline compilation)
//       until we get a new stripe-based scheduler.
// PLAIDML_EDSL_API plaidml_executable* plaidml_program_compile(  //
//     plaidml_error* err,                                        //
//     plaidml_program* program,                                  //
//     const char* target,                                        //
//     size_t ninputs,                                            //
//     plaidml_binding* inputs,                                   //
//     size_t noutputs,                                           //
//     plaidml_binding* outputs);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus