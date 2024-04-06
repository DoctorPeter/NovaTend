========================================================================
    DYNAMIC LINK LIBRARY : z-dbconnect-01 Project Overview
========================================================================

The z-dbconnect-01.dll provides access to user credential information database. 
This dll implements class DatabaseManager and class ODBCDatabaseManager.
DatabaseManager is abstract class. It provides general structure of class of 
access to database. ODBCDatabaseManager inherited from DatabaseManager. It
provides access to database via ODBC.