# LibrarySystem Database

## Overview

This directory contains the MySQL database scripts for the
**LibrarySystem** project.

Target database:

-   MySQL 8.4+
-   Character Set: utf8mb4
-   Storage Engine: InnoDB

## Directory

``` text
sql/
├── init_library.sql
├── seed_data.sql
└── README.md
```

## Schema

Core tables:

  Table              Description
------------------ -------------------------
  users              User information
  roles              Roles
  permissions        Permissions
  user_roles         User-role mapping
  role_permissions   Role-permission mapping
  categories         Book categories
  publishers         Publishers
  books              Book metadata
  book_copies        Physical book copies
  borrow_records     Borrow records

## Relationships

-   One category → many books
-   One publisher → many books
-   One book → many physical copies
-   One user → many borrow records
-   RBAC uses many-to-many relationships.

## Initialization

Create database and tables:

``` sql
SOURCE init_library.sql;
```

Load demo data:

``` sql
SOURCE seed_data.sql;
```

## Design Principles

-   BIGINT primary keys
-   snake_case naming
-   Foreign key constraints
-   InnoDB engine
-   utf8mb4 charset
-   RBAC authorization model
-   Separate book metadata from physical copies

## Future Plans

-   Reservation
-   Fine management
-   Statistics dashboard
-   REST/C/S architecture
-   Database migration scripts
