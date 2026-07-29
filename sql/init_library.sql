-- ===========================================
-- Library Management System Database
-- Version: 1.0
-- MySQL 8.0+
-- ===========================================

DROP DATABASE IF EXISTS library;
CREATE DATABASE library
DEFAULT CHARACTER SET utf8mb4
DEFAULT COLLATE utf8mb4_0900_ai_ci;
USE library;

SET NAMES utf8mb4;

CREATE TABLE roles(
 id BIGINT PRIMARY KEY AUTO_INCREMENT COMMENT '角色ID',
 code VARCHAR(50) NOT NULL UNIQUE COMMENT '角色编码',
 name VARCHAR(100) NOT NULL COMMENT '角色名称',
 description VARCHAR(255),
 created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
 updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB COMMENT='角色表';

CREATE TABLE permissions(
 id BIGINT PRIMARY KEY AUTO_INCREMENT,
 code VARCHAR(100) NOT NULL UNIQUE COMMENT '权限编码',
 name VARCHAR(100) NOT NULL,
 description VARCHAR(255),
 created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
 updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB COMMENT='权限表';

CREATE TABLE users(
 id BIGINT PRIMARY KEY AUTO_INCREMENT,
 username VARCHAR(50) NOT NULL UNIQUE,
 password VARCHAR(255) NOT NULL,
 name VARCHAR(50) NOT NULL,
 gender TINYINT NOT NULL DEFAULT 0 COMMENT '0未知1男2女',
 age INT,
 phone VARCHAR(20),
 enabled BOOLEAN NOT NULL DEFAULT TRUE,
 last_login_time DATETIME NULL,
 last_login_ip VARCHAR(45),
 deleted BOOLEAN NOT NULL DEFAULT FALSE,
 created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
 updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB COMMENT='用户表';

CREATE TABLE user_roles(
 user_id BIGINT NOT NULL,
 role_id BIGINT NOT NULL,
 PRIMARY KEY(user_id,role_id),
 CONSTRAINT fk_ur_user FOREIGN KEY(user_id) REFERENCES users(id),
 CONSTRAINT fk_ur_role FOREIGN KEY(role_id) REFERENCES roles(id)
) ENGINE=InnoDB COMMENT='用户角色关联';

CREATE TABLE role_permissions(
 role_id BIGINT NOT NULL,
 permission_id BIGINT NOT NULL,
 PRIMARY KEY(role_id,permission_id),
 CONSTRAINT fk_rp_role FOREIGN KEY(role_id) REFERENCES roles(id),
 CONSTRAINT fk_rp_perm FOREIGN KEY(permission_id) REFERENCES permissions(id)
) ENGINE=InnoDB COMMENT='角色权限关联';

CREATE TABLE categories(
 id BIGINT PRIMARY KEY AUTO_INCREMENT,
 name VARCHAR(100) NOT NULL UNIQUE,
 sort_order INT DEFAULT 0,
 description VARCHAR(255),
 created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
 updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB COMMENT='图书分类';

CREATE TABLE publishers(
 id BIGINT PRIMARY KEY AUTO_INCREMENT,
 name VARCHAR(200) NOT NULL UNIQUE,
 contact VARCHAR(100),
 website VARCHAR(255),
 created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
 updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB COMMENT='出版社';

CREATE TABLE books(
 id BIGINT PRIMARY KEY AUTO_INCREMENT,
 isbn VARCHAR(20) NOT NULL UNIQUE,
 title VARCHAR(200) NOT NULL,
 author VARCHAR(200) NOT NULL,
 publisher_id BIGINT,
 category_id BIGINT,
 publish_year YEAR,
 price DECIMAL(10,2),
 cover_url VARCHAR(500),
 description TEXT,
 status TINYINT NOT NULL DEFAULT 0 COMMENT '0正常1下架2停用',
 deleted BOOLEAN NOT NULL DEFAULT FALSE,
 created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
 updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
 CONSTRAINT fk_book_pub FOREIGN KEY(publisher_id) REFERENCES publishers(id),
 CONSTRAINT fk_book_cat FOREIGN KEY(category_id) REFERENCES categories(id)
) ENGINE=InnoDB COMMENT='图书信息';

CREATE TABLE book_copies(
 id BIGINT PRIMARY KEY AUTO_INCREMENT,
 book_id BIGINT NOT NULL,
 inventory_no VARCHAR(50) NOT NULL UNIQUE,
 location VARCHAR(100),
 status TINYINT NOT NULL DEFAULT 0 COMMENT '0可借1借出2丢失3损坏',
 created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
 updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
 CONSTRAINT fk_copy_book FOREIGN KEY(book_id) REFERENCES books(id)
) ENGINE=InnoDB COMMENT='图书副本';

CREATE TABLE borrow_records(
 id BIGINT PRIMARY KEY AUTO_INCREMENT,
 user_id BIGINT NOT NULL,
 copy_id BIGINT NOT NULL,
 operator_id BIGINT,
 borrow_time DATETIME NOT NULL,
 due_time DATETIME NOT NULL,
 return_time DATETIME,
 status TINYINT NOT NULL DEFAULT 0 COMMENT '0借阅中1已归还2逾期',
 remark VARCHAR(500),
 created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
 updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
 CONSTRAINT fk_br_user FOREIGN KEY(user_id) REFERENCES users(id),
 CONSTRAINT fk_br_copy FOREIGN KEY(copy_id) REFERENCES book_copies(id),
 CONSTRAINT fk_br_operator FOREIGN KEY(operator_id) REFERENCES users(id)
) ENGINE=InnoDB COMMENT='借阅记录';

CREATE INDEX idx_books_title ON books(title);
CREATE INDEX idx_books_author ON books(author);
CREATE INDEX idx_copy_status ON book_copies(status);
CREATE INDEX idx_br_user ON borrow_records(user_id);
CREATE INDEX idx_br_copy ON borrow_records(copy_id);
CREATE INDEX idx_br_status ON borrow_records(status);

INSERT INTO roles(code,name) VALUES
('ADMIN','系统管理员'),
('LIBRARIAN','图书管理员'),
('READER','读者');

INSERT INTO permissions(code,name) VALUES
('USER_VIEW','查看用户'),
('USER_ADD','新增用户'),
('USER_EDIT','编辑用户'),
('USER_DELETE','删除用户'),
('BOOK_VIEW','查看图书'),
('BOOK_ADD','新增图书'),
('BOOK_EDIT','编辑图书'),
('BOOK_DELETE','删除图书'),
('BOOK_BORROW','借阅图书'),
('BOOK_RETURN','归还图书');

INSERT INTO users(username,password,name)
VALUES('admin','admin123','系统管理员');

INSERT INTO user_roles VALUES(1,1);
