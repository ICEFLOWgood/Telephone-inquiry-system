#include"my.h"

HashNode*hashTable[HASH_TABLE_MAX_SIZE];//定义哈希数组；
int hash_table_size;//哈希表实际大小；
int res;
MYSQL my_connection;//定义MYSQL结构，连接句柄；
MYSQL_RES *res_ptr;//保存检索出的列；
MYSQL_ROW sqlrow;//保存返回的其中一列；

void hash_table_init()//初始化哈希表大小和哈希数组；
{
    hash_table_size = 0;
    memset(hashTable, 0, sizeof(HashNode*)*HASH_TABLE_MAX_SIZE);
}

unsigned int hash_table_hash_str(const char*skey)//字符串哈希算法函数；
{
    const signed char*p = (const signed char*)skey;
    unsigned int h = *p;
    if(h)
    {
        for(p+=1; *p!='\0'; p++)
        {
            h = (h<<5) - h + *p;
        }
    }
    return h;
}

/*
int main()//测试函数；
{
  //  char DBName[] = "Telephone";
  //  char DBUserName[] = "root";
  //  char DBUserPassword[] = "IceFlow2012";
    init_hash_table();
    update_hash_table();
    printf("哈希表实际大小：%d\n", hash_table_size);
    char a[256];
    printf("请输入要查询的信息：");
    scanf("%s", a);
    HashNode*ptest;
    ptest = hash_table_lookup(a);
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", ptest->infor->myname,
                                        ptest->infor->abbreviation,
                                        ptest->infor->full,
                                        ptest->infor->company,
                                        ptest->infor->privation,
                                        ptest->infor->extension,
                                        ptest->infor->emall);
    return 0;
}
*/

//free the memory of the hash table
void hash_table_release()
{
    int i;
    for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i)
    {
        if(hashTable[i])
        {
            HashNode* pHead = hashTable[i];
            while(pHead)
            {
                HashNode* pTemp = pHead;
                pHead = pHead->pNext;
                if(pTemp)
                {
                    free(pTemp->sKey);
                    free(pTemp->infor);
                    free(pTemp);
                }
            }
        }
    }
}


int update_hash_table()
{
    hash_table_release();
    init_hash_table();
    return 0;
}

int init_hash_table()
{
    char mysql_server_ip[] = "172.16.20.50";
    char mysqlDB_name[] = "Telephone";
    char mysql_name[] = "root";
    char mysql_password[] = "IceFlow2012";

    hash_table_init();//初始化哈希表大小和哈希数组；
    mysql_init(&my_connection);//初始化MYSQL结构；
    //数据库的连接；
    if(mysql_real_connect(&my_connection, 
                            mysql_server_ip, 
                            mysql_name,
                            mysql_password,
                            mysqlDB_name,
                            0,
                            NULL,
                            0))
    {
        printf("Database connection success\n");
        res = mysql_query(&my_connection, "select * from staffs");
        if(res)
        {
            printf("database select error:%s\n", mysql_error(&my_connection));
            return -1;
        }
        else
        {
            res_ptr = mysql_store_result(&my_connection);
            if(res_ptr)
            {
                printf("Retrieved %lu rows\n", (unsigned long)mysql_num_rows(res_ptr));//打印取回多少行；
                display_header();//建立哈希表；
                if(mysql_errno(&my_connection))
                {
                    fprintf(stderr, "Retrive error:%s\n", mysql_error(&my_connection));
                    return -1;
                }
            }
            mysql_free_result(res_ptr);
        }
        mysql_close(&my_connection);
        printf("Database connection closed.\n");
    }
    else
    {
        fprintf(stderr, "Connection failed\n");
        if(mysql_errno(&my_connection))
        {
            fprintf(stderr,"Connection error %d:%s\n", 
                                        mysql_errno(&my_connection), //错误消息编号；
                                        mysql_error(&my_connection));//返回包含错误消息的、由NULL终结的字符串；
            return -1;
        }
    }
    return 0;
}

void display_header()//建立哈希表；
{
    unsigned int num_fields;
    unsigned int i;
    MYSQL_ROW row;
    INFOR* NewInfor;
    
    num_fields = mysql_num_fields(res_ptr);
    while(row = mysql_fetch_row(res_ptr))
    {   
        for(i=1; i<num_fields; i++)
        {
            NewInfor = malloc(sizeof(INFOR));
            memset(NewInfor, 0, sizeof(INFOR));
            
            strcpy(NewInfor->myname, row[1]?row[1]:"NULL");
            strcpy(NewInfor->abbreviation, row[2]?row[2]:"NULL");
            strcpy(NewInfor->full, row[3]?row[3]:"NULL");
            strcpy(NewInfor->company, row[4]?row[4]:"NULL");
            strcpy(NewInfor->privation, row[5]?row[5]:"NULL");
            strcpy(NewInfor->extension, row[6]?row[6]:"NULL");
            strcpy(NewInfor->emall, row[7]?row[7]:"NULL");
            
            hash_table_insert(row[i]?row[i]:"NULL", NewInfor);//给每一列进行hash算法，插入hash表；
        }
    }
}

void hash_table_insert(const char* skey, INFOR* nvalue)//向哈希表中插入元素；
{
    if(hash_table_size >= HASH_TABLE_MAX_SIZE)
    {
        printf("Out of hash table memory!\n");
        return;
    }
    
    unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    HashNode* pHead = hashTable[pos];
    while(pHead)
    {   
        if(skey[0] == '\0')
        {
            return;
        }
        if(strcmp(pHead->sKey, skey) == 0 && strcmp(pHead->infor->emall, nvalue->emall) == 0)
        {
            printf("%s already exists!\n", skey);
            return;
        }
        pHead = pHead->pNext;
    }
    HashNode* pNewNode = (HashNode*)malloc(sizeof(HashNode));
    memset(pNewNode, 0, sizeof(HashNode));
    pNewNode->sKey = (char*)malloc(sizeof(char)*(strlen(skey)+1));
    strcpy(pNewNode->sKey, skey);
    pNewNode->infor = nvalue;
    pNewNode->pNext = hashTable[pos];
    hashTable[pos] = pNewNode;
    
    hash_table_size++;
}

HashNode* hn[64] = {0};
HashNode** hash_table_lookup(char* skey)//查找哈希表数据；
{

    int i;
    for(i=0; i<strlen(skey); i++)//去掉字符串后的回车符号；
    {
        if(skey[i]=='\n')
        {
            skey[i]='\0';
            break;
        }      
    }
    i = 0;
    memset(hn, 0, sizeof(hn));
    unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    if(hashTable[pos])
    {
        HashNode* pHead = hashTable[pos];
        while(pHead)
        {          
            if(strcmp(skey, pHead->sKey) == 0)
            {
                hn[i++] = pHead;
            }
            pHead = pHead->pNext;
        }
        if(pHead == NULL)
        {
            return hn;
        }
    }
    return NULL;
}



