<?PHP
class DbOraCnnx {
    // Conexion database
    protected static $DbOraCnnx;

    /**
     * Methodo de Conexion a la Bse de datos
     * 
     * @return bool false cuando falla / mysqli MySQLi object instance
     */
    public function cnnxDB() {    
        // Try and connect to the database
        if(!isset(self::$DbOraCnnx)) {
            // Load configuration as an array. Use the actual location of your configuration file
            //echo "Ruta Actual " .getcwd () ."<br>";
            //echo dirname(__FILE__) ."<br>";
            //echo $_SERVER['DOCUMENT_ROOT'] ."<br>";
            $DatCnnx = parse_ini_file($_SERVER['DOCUMENT_ROOT'] .'/general/oracle_ssa.ini'); 
           self::$DbOraCnnx = oci_connect($DatCnnx['usuario'],$DatCnnx['password'],$DatCnnx['servidor']."/".$DatCnnx['SID_ssa']);
        }

        // If DbOraCnnx was not successful, handle the error
        if(self::$DbOraCnnx === false) {
            // Handle error - notify administrator, log to a file, show an error screen, etc.
           // echo "Error en conexion";
            return false;
        }
        //echo "conexion Exitosa";
        return self::$DbOraCnnx;
    } // fin de function cnnxDB

    /**
     * Query the database
     *
     * @param $Consulta The query string
     * @return mixed The result of the mysqli::query() function
     */
    public function query($Consulta) {
        // Connect to the database
        $DbOraCnnx = $this->cnnxDB();

        // Query the database
		$result = oci_parse($DbOraCnnx,$Consulta);
        return $result;
    }

    /**
     * Fetch rows from the database (SELECT query)
     *
     * @param $Consulta The query string
     * @return bool False on failure / array Database rows on success
     */

    public function select( $Consulta) {
        $rows = array();
        //$result = $this->query($Consulta);

        $ConnId = $this->query( $Consulta);
        $result= oci_execute($ConnId);

        if(gettype($result) === "boolean")
        {    
            //echo "Fue tipo boolean <br>";
            if($result === false) {
                return false;
            }
            
        }
        else
        {
            //echo "Fue otro tipo  <br>";
            while ($row = oci_fetch_array($ConnId, OCI_ASSOC+OCI_RETURN_NULLS)) {
                $rows[] = $row;
            }
        }                
        return $rows;
    }
	
    /**
     * Fetch the last error from the database
     * 
     * @return string Database error message
     */
    public function error() {
        $DbOraCnnx = $this->cnnxDB();
        return $DbOraCnnx->error;
    }
	
	public function combo( $Consulta) {
        $rows = array();
        $ConnId = $this->query( $Consulta);
        $result= oci_execute($ConnId);     
        return $ConnId;
    }

    /**
     * Quote and escape value for use in a database query
     *
     * @param string $value The value to be quoted and escaped
     * @return string The quoted and escaped string
     */
    public function quote($value) {
        $DbOraCnnx = $this -> cnnxDB();
        return "'" . $DbOraCnnx -> real_escape_string($value) . "'";
    }
} // fin de class Db



?>