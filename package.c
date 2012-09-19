
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<mysql/mysql.h>
#include<Python.h>
#include <assert.h>

typedef struct Infor_Struct//员工信息结构体；
{
    char myname[32];
    char abbreviation[32];
    char full[32];
    char company[32];
    char privation[32];
    char extension[32];
    char emall[32];
}INFOR;

typedef struct HashNode_Struct//定义哈希数组类型；
{
    char* sKey;
    INFOR* infor;
    struct HashNode_Struct*pNext;
}HashNode;


static PyObject* hash_init_hash_table(PyObject*self, PyObject*args
                                     //   PyObject*Name, 
                                      //  PyObject*UserName,
                                      //  PyObject*UserPassword
                                        )
{
    int res;
    char* DBName;
    char* DBUserName;
    char* DBUserPassword;
    PyObject*retu;  
    res = PyArg_ParseTuple(args,
                            //Name,
                            //UserName,
                            //UserPassword,
                            "sss",
                            &DBName,
                            &DBUserName,
                            &DBUserPassword);
    if(!res)
    {
        return NULL;
    }
    res = init_hash_table(DBName, DBUserName, DBUserPassword);
    retu = (PyObject*)Py_BuildValue("i", res);
    return retu;
}

static PyObject* hash_update_hash_table(PyObject*self, PyObject*args
                                     //   PyObject*Name, 
                                      //  PyObject*UserName,
                                      //  PyObject*UserPassword
                                        )
{
    int res;
    char* DBName;
    char* DBUserName;
    char* DBUserPassword;
    PyObject*retu;  
    res = PyArg_ParseTuple(args,
                            //Name,
                            //UserName,
                            //UserPassword,
                            "sss",
                            &DBName,
                            &DBUserName,
                            &DBUserPassword);
    if(!res)
    {
        return NULL;
    }
    res = update_hash_table(DBName, DBUserName, DBUserPassword);
    retu = (PyObject*)Py_BuildValue("i", res);
    return retu;
}

static PyObject* hash_hash_table_lookup(PyObject*self, PyObject*args)
{
    int res;
    char* key;

    HashNode**result;
    PyObject* retu;
 
    res = PyArg_ParseTuple(args, "s", &key); 
    if(!res)
    {
        return Py_None;
    }
    
    result = hash_table_lookup(key);
	if(result == NULL)
	{
		return Py_None;
	}
    char str[4096];
    int i=0;
    memset(str, 0, sizeof(str));
    while(result[i])
    {
        strcat(str, result[i]->infor->myname);
        strcat(str, "\\");
        strcat(str, result[i]->infor->abbreviation);
        strcat(str, "\\");
        strcat(str, result[i]->infor->full);    
        strcat(str, "\\");
        strcat(str, result[i]->infor->company);    
        strcat(str, "\\");
        strcat(str, result[i]->infor->privation);    
        strcat(str, "\\");
        strcat(str, result[i]->infor->extension);    
        strcat(str, "\\");
        strcat(str, result[i]->infor->emall);
        strcat(str, "\\");
        i++;
    }
    retu = (PyObject*)Py_BuildValue("s", str);
    
	
	/*
    PyObject*pList = PyList_New(10);
    assert(PyList_Check(pList));
  printf("##################\t%s\n", result->infor->myname);
    PyList_Append(pList, Py_BuildValue("s", result->infor->myname));
  printf("##################\t%s\n", result->infor->abbreviation); 
    PyList_Append(pList, Py_BuildValue("s", result->infor->abbreviation)); 
  printf("##################\t%s\n", result->infor->full); 
    PyList_Append(pList, Py_BuildValue("s", result->infor->full));
  printf("##################\t%s\n", result->infor->company);
    PyList_Append(pList, Py_BuildValue("s", result->infor->company));
  printf("##################\t%s\n", result->infor->privation);
    PyList_Append(pList, Py_BuildValue("s", result->infor->privation));
  printf("##################\t%s\n", result->infor->extension);
    PyList_Append(pList, Py_BuildValue("s", result->infor->extension));
  printf("##################\t%s\n", result->infor->emall);
    PyList_Append(pList, Py_BuildValue("s", result->infor->emall));
PyObject* pValue = PyList_GetItem(pList, 1);
char* test;
PyArg_ParseTuple(pValue, "s", &test);
printf("********************************\n");
printf("*************%s\n", test);
printf("********************************\n");
*/
 //   return (PyObject*)pList;
    return retu;
}

static PyObject* hash_test(PyObject*self, PyObject*args)
{
    int res;
    res = test();
    return (PyObject*)Py_BuildValue("i",res);
}

static PyMethodDef hashMethods[] =
{
    {"init_hashtable", hash_init_hash_table, METH_VARARGS},
    {"get_info", hash_hash_table_lookup, METH_VARARGS},    
    {"update_hashtable", hash_update_hash_table, METH_VARARGS},
    {"testmodel", hash_test, METH_VARARGS},
    {NULL, NULL}
};

void inithash()
{
    Py_InitModule("hash", hashMethods);
}