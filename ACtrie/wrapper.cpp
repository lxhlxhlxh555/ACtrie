#include <Python.h>
#include "aho_corasick.hpp"

/****** wrap for python ********/

static void ACtrie_Delete(PyObject *ptr)
{
    aho_corasick::wtrie *pAC = static_cast<aho_corasick::wtrie *>(PyCapsule_GetPointer(ptr,NULL));
    delete pAC;
}

static PyObject* ACtrie_new(PyObject *self, PyObject* args)
{
    aho_corasick::wtrie *pAC = new aho_corasick::wtrie();
    return PyCapsule_New(pAC, NULL, ACtrie_Delete);
}

static PyObject* ACtrie_insert(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    const wchar_t * str;
    int ok = PyArg_ParseTuple(args, "Ou", &ac, &str);
    if(!ok) return NULL;
    
    aho_corasick::wtrie *trie = static_cast<aho_corasick::wtrie *>(PyCapsule_GetPointer(ac,NULL));
    trie->insert(str);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* ACtrie_match_all(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    const wchar_t * str;
    int ok = PyArg_ParseTuple(args, "Ou", &ac, &str);
    if(!ok) return NULL;
    aho_corasick::wtrie *trie = static_cast<aho_corasick::wtrie *>(PyCapsule_GetPointer(ac,NULL));
    auto result = trie->parse_text(str);
    PyObject* pList = PyList_New(result.size());
    unsigned long i = 0;
    for(auto&& emit : result) {
        PyList_SetItem(pList, i++, Py_BuildValue("lu", emit.get_start(), emit.get_keyword().c_str()));
    }
    return pList;
}

static PyObject* ACtrie_case_insensitive(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    int ok = PyArg_ParseTuple(args, "O", &ac);
    if(!ok) return NULL;
    
    aho_corasick::wtrie *trie = static_cast<aho_corasick::wtrie *>(PyCapsule_GetPointer(ac,NULL));
    trie->case_insensitive();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* ACtrie_remove_overlaps(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    int ok = PyArg_ParseTuple(args, "O", &ac);
    if(!ok) return NULL;
    
    aho_corasick::wtrie *trie = static_cast<aho_corasick::wtrie *>(PyCapsule_GetPointer(ac,NULL));
    trie->remove_overlaps();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* ACtrie_only_whole_words(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    int ok = PyArg_ParseTuple(args, "O", &ac);
    if(!ok) return NULL;
    
    aho_corasick::wtrie *trie = static_cast<aho_corasick::wtrie *>(PyCapsule_GetPointer(ac,NULL));
    trie->only_whole_words();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef Methods[] =
{
     { "new", ACtrie_new, METH_NOARGS, "create a ACAutomation Object" },
     { "insert", ACtrie_insert, METH_VARARGS, "insert string" },
     { "match_all", ACtrie_match_all, METH_VARARGS, "match all" },
     { "case_insensitive", ACtrie_case_insensitive, METH_VARARGS, "case_insensitive" },
     { "remove_overlaps", ACtrie_remove_overlaps, METH_VARARGS, "remove_overlaps" },
     { "only_whole_words", ACtrie_only_whole_words, METH_VARARGS, "only_whole_words" },
     { NULL, NULL, 0, NULL }
};

struct module_state {
    PyObject *error;
};

static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "ACtrie",
        NULL,
        sizeof(struct module_state),
        Methods,
        NULL,
        NULL,
        NULL,
        NULL
};

PyMODINIT_FUNC PyInit__ACtrie(void)
{
     PyModule_Create(&moduledef);
}
