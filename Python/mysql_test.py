# Python连接mysql服务器

import pymysql

con = pymysql.connect(host='localhost', port=3306,
                      database='test', user='root', password='123456789')

cursor = con.cursor()
cursor.execute(
    'create table user (id varchar(20) primary key,name varchar(20))')
cursor.execute('insert into user (id,name) values (%s,%s)', ['1', 'Michael'])
cursor.rowcount
con.commit()
cursor.close()
cursor = con.cursor()
cursor.execute('select * from user where id =%s', ('1',))
values = cursor.fetchall()
print(values)
cursor.close()
con.close()
