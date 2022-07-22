<?PHP
class DbCnnx {
    // Conexion database
    protected static $DBCnnx;

    /**
     * Methodo de Conexion a la Bse de datos
     * 
     * @return bool false cuando falla / mysqli MySQLi object instance
     */
    public function cnnxDB() {    
        // Try and connect to the database
        if(!isset(self::$DBCnnx)) {
            // Load configuration as an array. Use the actual location of your configuration file
            //echo "Ruta Actual " .getcwd () ."<br>";
            //echo dirname(__FILE__) ."<br>";
            //echo $_SERVER['DOCUMENT_ROOT'] ."<br>";
            $DatCnnx = parse_ini_file('../general/ssa_cnx.ini'); 
            if(is_array($DatCnnx))
            self::$DBCnnx = new mysqli($DatCnnx['servidor'],$DatCnnx['usuario'],$DatCnnx['password'],$DatCnnx['base_ssa']);
            else
                echo "Problema con lectura de archivo ini";
        }

        // If DBCnnx was not successful, handle the error
        if(self::$DBCnnx === false) {
            // Handle error - notify administrator, log to a file, show an error screen, etc.
           // echo "Error en conexion";
            return false;
        }
        //echo "conexion Exitosa";
        return self::$DBCnnx;
    } // fin de function cnnxDB

    /**
     * Query the database
     *
     * @param $Consulta The query string
     * @return mixed The result of the mysqli::query() function
     */
    public function query($Consulta) {
        // Connect to the database
        $DBCnnx = $this->cnnxDB();

        // Query the database
        $result = $DBCnnx->query($Consulta);

        return $result;
    }

    /**
     * Fetch rows from the database (SELECT query)
     *
     * @param $Consulta The query string
     * @return bool False on failure / array Database rows on success
     */
    public function select($Consulta) {
        $rows = array();
        $result = $this->query($Consulta);
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
            while ($row = $result->fetch_assoc()) {
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
        $DBCnnx = $this->cnnxDB();
        return $DBCnnx->error;
    }

    /**
     * Quote and escape value for use in a database query
     *
     * @param string $value The value to be quoted and escaped
     * @return string The quoted and escaped string
     */
    public function quote($value) {
        $DBCnnx = $this -> cnnxDB();
        return "'" . $DBCnnx -> real_escape_string($value) . "'";
    }
} // fin de class Db



?>