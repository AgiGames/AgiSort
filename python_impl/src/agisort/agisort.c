// NOTE: THIS IS NOT DONE YET! Read agisort.py.

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <math.h>

static PyObject *agisort(PyObject* self, PyObject* args) {
    PyObject *input_list;
    PyObject *score;

    if (!PyArg_ParseTuple(args, "OO", &input_list, &score))
        return NULL;

    Py_ssize_t n = PyObject_Length(input_list);
    if (n == 0) {
        return input_list;
    }

    PyObject* min_score = PyObject_CallOneArg(score, PyList_GET_ITEM(input_list, 0));
    if (min_score == NULL) {
        return input_list;
    }

    PyObject* max_score = min_score;
    Py_INCREF(min_score);

    PyObject *scores = PyList_New(n);
    Py_INCREF(min_score);
    PyList_SetItem(scores, 0, min_score);

    for (Py_ssize_t i = 1; i < n; ++i) {
        PyObject* ith_score = PyObject_CallOneArg(score, PyList_GET_ITEM(input_list, i));
        Py_INCREF(ith_score);
        PyList_SetItem(scores, i, ith_score);

        if (ith_score == NULL) {
            return NULL;
        }

        size_t need_count = 0;

        int smaller = PyObject_RichCompareBool(
            ith_score,
            min_score,
            Py_LT
        );
        if (smaller < 0) {
            Py_DECREF(ith_score);
            return NULL;
        }

        if (smaller) {
            Py_DECREF(min_score);
            need_count += 1;
            min_score = ith_score;
        }

        int bigger = PyObject_RichCompareBool(
            ith_score,
            max_score,
            Py_GT
        );
        if (bigger < 0) {
            Py_DECREF(ith_score);
            return NULL;
        }

        if (bigger) {
            Py_DECREF(max_score);
            need_count += 1;
            max_score = ith_score;
        }

        if (need_count == 2) {
            Py_INCREF(ith_score);
        }
        else if (need_count == 0) {
            Py_DECREF(ith_score);
        }
    }

    int equal = PyObject_RichCompareBool(
            min_score,
            max_score,
            Py_EQ
        );
    if (equal < 0) {
        Py_DECREF(scores);
        Py_DECREF(min_score);
        Py_DECREF(max_score);
    }

    if (equal) {
        Py_DECREF(scores);
        Py_DECREF(min_score);
        Py_DECREF(max_score);

        return input_list;
    }

    PyObject *heaps = PyList_New(n);
    if (heaps == NULL)
        return NULL;

    for (Py_ssize_t i = 0; i < n; ++i) {
        PyObject *heap = PyList_New(0);
        if (heap == NULL) {
            Py_DECREF(heaps);
            return NULL;
        }

        PyList_SET_ITEM(heaps, i, heap);
    }

    PyObject* denom = PyNumber_Subtract(max_score, min_score);

    PyObject *n_obj = PyLong_FromSsize_t(n);
    if (n_obj == NULL)
        return NULL;

    PyObject *one = PyLong_FromLong(1);
    if (one == NULL) {
        return NULL;
    }

    PyObject *scaler = PyNumber_Subtract(n_obj, one);

    for (Py_ssize_t i = 0; i < n; ++i) {
        PyObject* ith_score = PyList_GET_ITEM(scores, i);
        double heap_index_double = PyFloat_AsDouble(PyNumber_Multiply(PyNumber_Divide(PyNumber_Subtract(ith_score, min_score), denom), scaler));
        Py_ssize_t heap_index = floor(heap_index_double);

        PyObject* ith_heap = PyList_GET_ITEM(heaps, heap_index);

    }
}