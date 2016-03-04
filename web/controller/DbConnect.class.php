<?php
if (!file_exists("../db_connection.local.php"))
    require_once "../db_connection.global.php";
else
    require_once "../db_connection.local.php";
/**
* Realiza a conexão e as operações no BD
*/
class DbConnect
{
    private $conn;
    function __construct()
    {
        $this->conn = new PDO('mysql:host='.DbConfig::host.';dbname='.DbConfig::dbname.'', DbConfig::user, DbConfig::password,
            array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES utf8",
                PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION) );
    }

    public function getConnection() {
        return $this->conn;
    }
}