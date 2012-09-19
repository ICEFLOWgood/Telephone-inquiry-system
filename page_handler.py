#!/usr/bin/env python
#-*-coding:utf-8-*-
from   Cheetah.Template import Template
def inerr(env,bodysize,input,output):
        scgi_err_info=Template(file="/var/www/htdocs/scgi-bin/errinfo.tmpl")
        output.write(str(scgi_err_info))

def index(env,bodysize,input,output):
        f_dict={'addinfo2':'欢迎进入电话查询系统','addinfo3':'信息查询','addinfo4':'信息添加',\
                'addinfo5':'信息删除','addinfo6':'信息修改'}
        t_index=Template(file="/var/www/htdocs/scgi-bin/index.tmpl",searchList=[f_dict])
        output.write(str(t_index))
def check(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/first.tmpl")
        t.addmessage = '请输入查找信息'
        output.write(str(t))
def add(env,bodysize,input,output):
        f_dict={'info1':'姓名','info2':'全拼','info3':'简拼','info4':'个人电话','info5':'公司电话','info6':\
              '分机号','info7':'邮箱地址'}
        t = Template(file="/var/www/htdocs/scgi-bin/add.tmpl",searchList=[f_dict])
        output.write(str(t))
def dele(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/del.tmpl")
        t.info1='请输入删除姓名'
        output.write(str(t))
def change(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/change.tmpl")
        t.info1='请输入姓名'
        output.write(str(t))
def add_finsh(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/add_finsh.tmpl")
        t.info1='添加已完成'
        output.write(str(t))
def add_error(env,bodysize,input,output,msg):
        t = Template(file="/var/www/htdocs/scgi-bin/add_error.tmpl")
        t.info1='已存在'
	t.info2=msg
        output.write(str(t))
def dele_finsh(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/del_finsh.tmpl")
        t.info1='已删除！'
        output.write(str(t))
def dele_error(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/del_error.tmpl")
        t.info1='删除失败！'
        output.write(str(t))
def select_finsh(env,bodysize,input,output,result):
        f_dict={'message1':'姓名:','message2':'全拼:','message3':'简拼:','message4':'个人电话:','message5':\
	'公司电话:','message6':'分机号:','message7':'邮箱地址:','info1':result[0],'info2':result[1],'info3':result[2],'info4':result[3],'info5':result[4],'info6':result[5],'info7':result[6]}
        t = Template(file="/var/www/htdocs/scgi-bin/select_finsh.tmpl",searchList=[f_dict])
        output.write(str(t))
def select_error(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/select_error.tmpl")
        t.info1='无此用户'
        output.write(str(t))
def change_on(env,bodysize,input,output,result):
        f_dict={'message1':'姓名:','message2':'全拼:','message3':'简拼:','message4':'个人电话:','message5':\
	'公司电话:','message6':'分机号:','message7':'邮箱地址:','message8':'旧姓名:','info1':result[0],'info2':result[1],'info3':result[2],'info4':result[3],'info5':result[4],'info6':result[5],'info7':result[6],'info8':result[7]}
        t = Template(file="/var/www/htdocs/scgi-bin/change_on.tmpl",searchList=[f_dict])
        output.write(str(t))
def change_finsh(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/change_finsh.tmpl")
        t.info1='更新成功'
        output.write(str(t))
def change_error(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/change_error.tmpl")
        t.info1='更新失败'
        output.write(str(t))
def no_null(env,bodysize,input,output):
        t = Template(file="/var/www/htdocs/scgi-bin/null_error.tmpl")
	t.info1='姓名、全拼、简拼、邮箱不能为空'
	output.write(str(t))
	
