/*
 * OWL - an OCaml numerical library for scientific computing
 * Copyright (c) 2016-2017 Liang Wang <liang.wang@cl.cam.ac.uk>
 */

#include "owl_macros.h"

#ifndef NUMBER
#define NUMBER double
void __dumb_fun() {};  // define a dumb to avoid warnings
#endif /* NUMBER */

#ifndef STOPFN
#define STOPFN(X, Y) (X < Y)
#endif /* STOPFN */

// function to compare two arrays
#ifdef FUN0

CAMLprim value FUN0(value vN, value vX, value vY)
{
  CAMLparam3(vN, vX, vY);
  int N = Long_val(vN);

  struct caml_ba_array *big_X = Caml_ba_array_val(vX);
  CAMLunused int dim_X = *big_X->dim;
  NUMBER *X_data = ((NUMBER *) big_X->data);

  struct caml_ba_array *big_Y = Caml_ba_array_val(vY);
  CAMLunused int dim_Y = *big_Y->dim;
  NUMBER *Y_data = ((NUMBER *) big_Y->data);

  NUMBER *start_x, *stop_x, *start_y;

  caml_enter_blocking_section();  /* Allow other threads */

  start_x = X_data;
  stop_x = start_x + N;
  start_y = Y_data;

  int r = 1;

  while (start_x != stop_x) {
    NUMBER x = *start_x;
    NUMBER y = *start_y;

    if (STOPFN(x, y)) {
      r = 0;
      break;
    }

    start_x += 1;
    start_y += 1;
  };

  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(r));
}

#endif /* FUN0 */


// function to compare an array to zero
#ifdef FUN1

CAMLprim value FUN1(value vN, value vX)
{
  CAMLparam2(vN, vX);
  int N = Long_val(vN);

  struct caml_ba_array *big_X = Caml_ba_array_val(vX);
  CAMLunused int dim_X = *big_X->dim;
  NUMBER *X_data = ((NUMBER *) big_X->data);

  NUMBER *start_x, *stop_x;

  caml_enter_blocking_section();  /* Allow other threads */

  start_x = X_data;
  stop_x = start_x + N;

  int r = 1;

  while (start_x != stop_x) {
    NUMBER x = *start_x;

    if (STOPFN(x)) {
      r = 0;
      break;
    }

    start_x += 1;
  };

  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(r));
}

#endif /* FUN1 */


// function to count number of non-zero elements
#ifdef FUN2

CAMLprim value FUN2(value vN, value vX)
{
  CAMLparam2(vN, vX);
  int N = Long_val(vN);

  struct caml_ba_array *big_X = Caml_ba_array_val(vX);
  CAMLunused int dim_X = *big_X->dim;
  NUMBER *X_data = ((NUMBER *) big_X->data);

  NUMBER *start_x, *stop_x;

  caml_enter_blocking_section();  /* Allow other threads */

  start_x = X_data;
  stop_x = start_x + N;

  int r = 0;

  while (start_x != stop_x) {
    NUMBER x = *start_x;
    if (CHECKFN(x)) r += 1;
    start_x += 1;
  };

  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(r));
}

#endif /* FUN2 */


// function to perform in-place mapping of elements in x
#ifdef FUN3

CAMLprim value FUN3(value vN, value vX)
{
  CAMLparam2(vN, vX);
  int N = Long_val(vN);

  struct caml_ba_array *big_X = Caml_ba_array_val(vX);
  CAMLunused int dim_X = *big_X->dim;
  NUMBER *X_data = ((NUMBER *) big_X->data);

  NUMBER *start_x, *stop_x;

  caml_enter_blocking_section();  /* Allow other threads */

  start_x = X_data;
  stop_x = start_x + N;

  int r = 0;

  while (start_x != stop_x) {
    NUMBER x = *start_x;
    *start_x = (MAPFN(x));
    start_x += 1;
  };

  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(r));
}

#endif /* FUN3 */


// function to perform mapping of elements from x to y
#ifdef FUN4

CAMLprim value FUN4(value vN, value vX, value vY)
{
  CAMLparam3(vN, vX, vY);
  int N = Long_val(vN);

  struct caml_ba_array *big_X = Caml_ba_array_val(vX);
  CAMLunused int dim_X = *big_X->dim;
  NUMBER *X_data = ((NUMBER *) big_X->data);

  struct caml_ba_array *big_Y = Caml_ba_array_val(vY);
  CAMLunused int dim_Y = *big_Y->dim;
  NUMBER1 *Y_data = ((NUMBER1 *) big_Y->data);

  NUMBER *start_x, *stop_x;
  NUMBER1 *start_y;

  caml_enter_blocking_section();  /* Allow other threads */

  start_x = X_data;
  stop_x = start_x + N;
  start_y = Y_data;

  int r = 1;

  while (start_x != stop_x) {
    NUMBER x = *start_x;
    *start_y = (MAPFN(x));

    start_x += 1;
    start_y += 1;
  };

  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(r));
}

#endif /* FUN4 */


// function to fold all the elements in x
#ifdef FUN5

CAMLprim value FUN5(value vN, value vX)
{
  CAMLparam2(vN, vX);
  int N = Long_val(vN);

  struct caml_ba_array *big_X = Caml_ba_array_val(vX);
  CAMLunused int dim_X = *big_X->dim;
  NUMBER *X_data = ((NUMBER *) big_X->data);

  NUMBER *start_x, *stop_x;

  caml_enter_blocking_section();  /* Allow other threads */

  start_x = X_data;
  stop_x = start_x + N;

  NUMBER1 r = 0.;

  while (start_x != stop_x) {
    NUMBER x = *start_x;
    r += (MAPFN(x));
    start_x += 1;
  };

  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(caml_copy_double(r));
}

#endif /* FUN5 */


#undef NUMBER
#undef STOPFN
#undef CHECKFN
#undef NUMBER1
#undef MAPFN
#undef FUN0
#undef FUN1
#undef FUN2
#undef FUN3
#undef FUN4
#undef FUN5
