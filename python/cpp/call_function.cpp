// call_function.c - A sample of calling python functions from C code
//
//  > PYTHONPATH=$( pwd ) ./call_function py_function multiply
//  Attempting to load python module: py_function
//  The result of 12345 x 6789 : 83810205
//  Return of call : 83810205
//
#include <Python.h>

#include <iostream>

int main(int argc, char* argv[]) {
  int i;
  PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;

  if(argc < 3) {
    printf("Usage: exe_name python_source function_name\n");
    return 1;
  }

  // Initialize the Python Interpreter
  Py_Initialize();

  // Build the name object
  pName = PyUnicode_FromString(argv[1]);

  // Load the module object
  std::cout << "Attempting to load python module: " << PyUnicode_AsUTF8(pName) << std::endl;
  if((pModule = PyImport_Import(pName)) == nullptr) {
  //if((pModule = PyImport_ImportModule(argv[1])) == nullptr) {
    std::cout << "FAILED to import the module " << argv[1] << std::endl;
    return -1;
  }

  // pDict is a borrowed reference
  pDict = PyModule_GetDict(pModule);

  // pFunc is also a borrowed reference
  pFunc = PyDict_GetItemString(pDict, argv[2]);

  if(PyCallable_Check(pFunc)) {
    // Prepare the argument list for the call
    if(argc > 3) {
      pArgs = PyTuple_New(argc - 3);
      for(i = 0; i < argc - 3; i++) {
        pValue = PyLong_FromLong(atoi(argv[i + 3]));
        if(!pValue) {
          PyErr_Print();
          return 1;
        }
        PyTuple_SetItem(pArgs, i, pValue);
      }

      pValue = PyObject_CallObject(pFunc, pArgs);

      if(pArgs != NULL) {
        Py_DECREF(pArgs);
      }
    } else {
      pValue = PyObject_CallObject(pFunc, NULL);
    }

    if(pValue != NULL) {
      printf("Return of call : %ld\n", PyLong_AsLong(pValue));
      Py_DECREF(pValue);
    } else {
      PyErr_Print();
    }
  } else {
    PyErr_Print();
  }

  // Clean up
  Py_DECREF(pModule);
  Py_DECREF(pName);

  // Finish the Python Interpreter
  Py_Finalize();

  return 0;
}
