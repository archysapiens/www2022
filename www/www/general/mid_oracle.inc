<?php

/*****************************************
*
* Funcion : ejecutaSQLOracle
* Objetivo: Ejecutar Instrucciones SQL Oracle
*
* PARAMETROS: 
* $SQL      : Postulado SQL
* $TagEnvio : Identificador de la consulta
* REGRESO
* $RESULTADO El resultado de la ejecucion de
*           SQL
*******************************************/

function ejecutaSQLOracle($SQL, $TagEnvio){

date_default_timezone_set('America/Mexico_City');
$FechaProceso = date("YmdHis");
$Path="../staging/oracle/";

$IdArchivoSQL=$Path.$TagEnvio.$FechaProceso.".ora";
$IdArchivoSQLRespuesta=$Path.$TagEnvio.$FechaProceso.".res";
$IdArchivoSQLBandera=$Path.$TagEnvio.$FechaProceso.".bnd";

$GestorArchivoSQL = fopen($IdArchivoSQL, "w");

if (!$GestorArchivoSQL) {
	echo "ejecutaSQLOracle IdArchivoSQL>>".$IdArchivoSQL."<<";
}else{

	fwrite($GestorArchivoSQL, $SQL);
	fclose($GestorArchivoSQL);

	while(!file_exists($IdArchivoSQLBandera))
		sleep(1);
	$myfile = fopen($IdArchivoSQLRespuesta, "r") or die("Unable to open file!".$IdArchivoSQLRespuesta);

// Output one line until end-of-file

	while(!feof($myfile)) {
    	$Respuesta[] = fgets($myfile);
	}
	fclose($myfile);
	return $Respuesta

}// fin del if

}// fin de ejecutaSQLOracle

?>