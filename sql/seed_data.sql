#测试数据

USE library;

INSERT INTO categories(name,sort_order,description) VALUES
('计算机',1,'计算机类'),
('文学',2,'文学类'),
('数学',3,'数学类'),
('历史',4,'历史类');

INSERT INTO publishers(name,website) VALUES
('机械工业出版社','https://www.cmpbook.com'),
('人民邮电出版社','https://www.ptpress.com.cn'),
('清华大学出版社','https://www.tup.com.cn');

INSERT INTO books(isbn,title,author,publisher_id,category_id,publish_year,price,description)
VALUES
('9787111213826','C++ Primer','Stanley B. Lippman',1,1,2020,128.00,'经典C++教材'),
('9787115545381','Effective Modern C++','Scott Meyers',1,1,2021,89.00,'现代C++最佳实践'),
('9787302511854','数据库系统概论','王珊',3,1,2022,69.00,'数据库教材'),
('9787115428028','计算机网络','谢希仁',2,1,2021,59.00,'计算机网络教材');

INSERT INTO book_copies(book_id,inventory_no,location,status) VALUES
(1,'CP202600001','A-01-01',0),
(1,'CP202600002','A-01-01',0),
(1,'CP202600003','A-01-02',1),
(2,'EMC202600001','A-02-01',0),
(2,'EMC202600002','A-02-01',0),
(3,'DB202600001','B-01-01',0),
(3,'DB202600002','B-01-02',2),
(4,'NW202600001','B-02-01',0);

INSERT INTO users(username,password,name,gender,age,phone)
VALUES
('reader1','123456','张三',1,22,'13800000001'),
('reader2','123456','李四',2,21,'13800000002'),
('librarian','123456','管理员A',1,30,'13800000003');

INSERT INTO user_roles(user_id,role_id) VALUES
(2,3),
(3,3),
(4,2);

INSERT INTO role_permissions(role_id,permission_id)
SELECT 1,id FROM permissions;

INSERT INTO role_permissions(role_id,permission_id)
SELECT 2,id FROM permissions WHERE code IN
('BOOK_VIEW','BOOK_ADD','BOOK_EDIT','BOOK_DELETE','BOOK_BORROW','BOOK_RETURN');

INSERT INTO role_permissions(role_id,permission_id)
SELECT 3,id FROM permissions WHERE code IN
('BOOK_VIEW','BOOK_BORROW','BOOK_RETURN');

INSERT INTO borrow_records(user_id,copy_id,operator_id,borrow_time,due_time,status,remark)
VALUES
(2,3,4,NOW(),DATE_ADD(NOW(),INTERVAL 30 DAY),0,'正常借阅');
