#!/usr/bin/env python
#-*-coding:utf-8-*a-
import MySQLdb
import hash
class sql():
	def __init__(self,host='172.16.20.50',user='root',passwd='IceFlow2012',db='Telephone'):
		self.host = host
		self.user = user
		self.passwd = passwd
		self.db = db
		self.sql_object = MySQLdb.connect(host,user,passwd,db)
		self.cur_object = self.sql_object.cursor()
		hash.init_hashtable(db,user,passwd)
	def select(self,info):
		result = hash.get_info(info)
		return result
	def add(self,a,b,c,d,e,f,g):
		self.cur_object.execute("insert into staffs(Name,Abbreviation,Full,Company,Privation,Extension,Email) values('"+a+"','"+b+"','"+c+"','"+d+"','"+e+"','"+f+"','"+g+"')")
		row = self.cur_object.rowcount
		#self.cur_object.close()
		self.sql_object.commit()
		#self.sql_object.close()
		return row 
	def delete(self,dele_name):
		self.cur_object.execute("delete from staffs where name = '"+dele_name+"'")
		row = self.cur_object.rowcount
                #self.cur_object.close()
                self.sql_object.commit()
                #self.sql_object.close()
                return row
	def reload_sql(self):
		hash.update_hashtable(self.db,self.user,self.passwd)
	def change(self,alist):
		print alist
		self.cur_object.execute("update staffs set Name='"+alist[1]+"',Abbreviation='"+alist[2]+"',FULL='"+alist[3]+"',Company='"+alist[4]+"',Privation='"+alist[5]+"',Extension='"+alist[6]+"',Email='"+alist[7]+"' where Name ='"+alist[0]+"'")
		row = self.cur_object.rowcount
		self.sql_object.commit()
		return row
