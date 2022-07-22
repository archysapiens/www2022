<?php
 
/**
 * ac_db.inc.php: Database class using the PHP OCI8 extension
 * @package Oracle
 */
 
//namespace Oracle;
 
//require('ac_cred_inc.php');
 
/**
 * Oracle Database access methods
 * @package Oracle
 * @subpackage Db
 */
class DbOracle {
 
    /**
     * @var Variable para conexion
     * @access protected
     */
    protected $conn = null;
    /**
     * @var resource The Statement Resource Identifier
     * @access protected
     */
    protected $stid = null;
    /**
     * @var integer The number of rows to prefetch with queries
     * @access protected
     */
    protected $prefetch = 100;

/**
     * Constructor de conexion ala BD
     * @param string $module Module text for End-to-End Application Tracing
     * @param string $cid Client Identifier for End-to-End Application Tracing
     */
    function __construct($module, $cid) {
        $DatCnnx = parse_ini_file($_SERVER['DOCUMENT_ROOT'] .'/transparencia/general/oracle.ini'); 
/**
        echo  "usuario    >>". $DatCnnx['usuario']  . "<< <br>   ";
        echo  "password   >>". $DatCnnx['password'] . "<< <br> ";
        echo  "servidor   >>". $DatCnnx['servidor'] . "<< <br> ";
        echo  "base_ssa   >>". $DatCnnx['base_ssa'] . "<< <br> ";
**/

        $this->conn = @oci_pconnect($DatCnnx['usuario'],$DatCnnx['password'],$DatCnnx['servidor']."/".$DatCnnx['base_ssa'], $DatCnnx['CHARSET']);

        //echo "Despues de conetar <bR>";
        if (!$this->conn) {
            $m = oci_error();
            throw new \Exception('SSA No se hay conexión a la BD: ' . $m['message']);
            echo "SSA No se hay conexión a la BD: " . $m['message'];
        }
        // Record the "name" of the web user, the client info and the module.
        // These are used for end-to-end tracing in the DB.
        oci_set_client_info($this->conn, $DatCnnx['CLIENT_INFO']);
        oci_set_module_name($this->conn, $module);
        oci_set_client_identifier($this->conn, $cid);
    }
 
    /**
     * Destructor closes the statement and connection
     */
    function __destruct() {
        if ($this->stid)
            oci_free_statement($this->stid);
        if ($this->conn)
            oci_close($this->conn);
    }

/**
     * Run a SQL or PL/SQL statement
     *
     * Call like:
     *     Db::execute("insert into mytab values (:c1, :c2)",
     *                 "Insert data", array(array(":c1", $c1, -1),
     *                                      array(":c2", $c2, -1)))
     *
     * For returned bind values:
     *     Db::execute("begin :r := myfunc(:p); end",
     *                 "Call func", array(array(":r", &$r, 20),
     *                                    array(":p", $p, -1)))
     *
     * Note: this performs a commit.
     *
     * @param string $sql The statement to run
     * @param string $action Action text for End-to-End Application Tracing
     * @param array $bindvars Binds. An array of (bv_name, php_variable, length)
     */
    public function execute($sql, $action, $bindvars = array()) {
        $this->stid = oci_parse($this->conn, $sql);
        if ($this->prefetch >= 0) {
            oci_set_prefetch($this->stid, $this->prefetch);
        }
        foreach ($bindvars as $bv) {
            // oci_bind_by_name(resource, bv_name, php_variable, length)
            oci_bind_by_name($this->stid, $bv[0], $bv[1], $bv[2]);
        }
        oci_set_action($this->conn, $action);
        oci_execute($this->stid);              // will auto commit
    }
 
    /**
     * Run a query and return all rows.
     *
     * @param string $sql A query to run and return all rows
     * @param string $action Action text for End-to-End Application Tracing
     * @param array $bindvars Binds. An array of (bv_name, php_variable, length)
     * @return array An array of rows
     */
    public function execFetchAll($sql, $action, $bindvars = array()) {
        $this->execute($sql, $action, $bindvars);
        oci_fetch_all($this->stid, $res, 0, -1, OCI_FETCHSTATEMENT_BY_ROW);
        $this->stid = null;  // free the statement resource
        return($res);
    }
 
}//Db
 
?>