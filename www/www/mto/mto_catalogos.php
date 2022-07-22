<?php
//
// mto_catalogos
// Construye los archivos que serviran como catalogos
// Fecha: 15-nov-2016

require('../general/generales.inc');
require('../scratch/ac_db_pn.php');
include "../general/DBC.php";

$db = new DbOracle("pro_nomina", "ArchiSoft");
$dbMysql = new DbCnnx();
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

$GestorArchivoCatPtos = fopen("cat_puestos.txt", "w");
if (!$GestorArchivoCatPtos)
		echo "<br> Error al abrir archivo Error >>cat_puestos.txt<< <br>";
else{
	$sql = "select trim(codigo) codigo from cat_puestos";
	$res = $db->execFetchAll($sql, "pro_nomina");
	foreach ($res as $row) {
		$CODIGO =$row['CODIGO']."\n";
		fwrite($GestorArchivoCatPtos, $CODIGO);
	}// fin foreach
	fclose($GestorArchivoCatPtos);
}

//  Seccion para crear catalogos de estados 

$GestorArchivoEdos = fopen("cat_estados.txt", "w");
if (!$GestorArchivoEdos) 
		echo "<br> Error al abrir archivo Error >>cat_estados.txt<< <br>" ;
else{
	$sql = "select trim(id_estado) id_estado from cat_estados";
	$res = $db->execFetchAll($sql, "pro_nomina");
	foreach ($res as $row) {
		$ESTADO =$row['ID_ESTADO']."\n";
		fwrite($GestorArchivoEdos, $ESTADO);
	}// fin foreach
	fclose($GestorArchivoEdos);
}// fin si

////////////////////////////////////////////////////////////////////////
//  seccion para crear catalogo Municipios
//  Regla que atiende fncValidaDI_26
////////////////////////////////////////////////////////////////////////

	$sql = "select trim(id_estado) id_estado from cat_municipios group by trim(id_estado)";
	$res = $db->execFetchAll($sql, "pro_nomina");
	foreach ($res as $row) {
		$ESTADO =$row['ID_ESTADO'];
		$dbMpio = new DbOracle("pro_nomina", "ArchiSoft");
		$sqlMpio = "select id_municipio from cat_municipios
					where id_estado='$ESTADO'";
		$resMpio = $dbMpio->execFetchAll($sqlMpio, "pro_nomina");
		if(is_array ( $resMpio)){
			$GestorArchivoMpios = fopen("mpio_$ESTADO.txt", "w");
			if (!$GestorArchivoMpios) 
					echo "<br> Error al abrir archivo Error >>"."mpio_$ESTADO.txt"."<< <br>";
			else{
				foreach ($resMpio as $rowMpio) {
					$MPIO =$rowMpio['ID_MUNICIPIO']."\n";
					fwrite($GestorArchivoMpios, $MPIO);
				}	
				fclose($GestorArchivoMpios);
			}
		}// fin del if de validacion de array
	}// fin foreach


////////////////////////////////////////////////////////////////////////
//  seccion para crear catalogo UR
//  Regla que atiende fncValidaDI_15
////////////////////////////////////////////////////////////////////////

$GestorArchivoUR = fopen("cat_ur.txt", "w");
if (!$GestorArchivoUR) 
		echo "<br> Error al abrir archivo Error >>cat_ur.txt<< <br>" ;
else{

	$sql = "select ur from cat_ur order by ur";
	$res = $db->execFetchAll($sql, "pro_nomina");
	foreach ($res as $row) {
		$UR =$row['UR']."\n";
		fwrite($GestorArchivoUR, $UR);
	}// fin foreach
	fclose($GestorArchivoUR);
} // fin if 


////////////////////////////////////////////////////////////////////////
//  seccion para crear catalogo para Estructura Programatica otros
//  Regla que atiende fncDirectivaCalidad_1
////////////////////////////////////////////////////////////////////////

$GestorArchivoEPOtros = fopen("cat_ep_otros.txt", "w");
if (!$GestorArchivoEPOtros)
		echo "<br> Error al abrir archivo Error >>cat_ep_otros.txt<< <br>";
else{
	$sql = "SELECT CONCAT(ctEP_UR,ctEP_GF, ctEP_FN,  LPAD(ctEP_SF,2,'0'), 
					LPAD(ctEP_PG,2,'0'),
					LPAD(ctEP_AI,3,'0'), ctEP_PP ) as EP  
					FROM ctestructura_programatica_gral
					WHERE ctEP_Estatus='1'";

	$res = $dbMysql->select($sql, "pro_nomina");
	foreach ($res as $row) {
		$EP =$row['EP']."\n";
		fwrite($GestorArchivoEPOtros, $EP);
	}// fin foreach
	fclose($GestorArchivoEPOtros);
}

////////////////////////////////////////////////////////////////////////
//  seccion para crear catalogo para Estructura Programatica Cancelados
//  Regla que atiende fncDirectivaCalidad_1
////////////////////////////////////////////////////////////////////////

$GestorArchivoEPCan = fopen("cat_ep_camcelados.txt", "w");
if (!$GestorArchivoEPCan)
		echo "<br> Error al abrir archivo Error >>cat_ep_camcelados.txt<< <br>";
else{
	$sql = "SELECT CONCAT(ctEP_UR,ctEP_GF, ctEP_FN,  LPAD(ctEP_SF,2,'0'), 
					LPAD(ctEP_PG,2,'0'),
					LPAD(ctEP_AI,3,'0'), ctEP_PP ) as EP 
					FROM ctestructura_programatica_gral	";

	$res = $dbMysql->select($sql, "pro_nomina");
	foreach ($res as $row) {
		$EP =$row['EP']."\n";
		fwrite($GestorArchivoEPCan, $EP);
	}// fin foreach
	fclose($GestorArchivoEPCan);
}



////////////////////////////////////////////////////////////////////////
//  seccion para crear catalogo partidas
//  Regla que atiende fncValidaDI_22
////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////
//  seccion para crear catalogo de productos de nomina
//  Regla que atiende Productos de Nomina y Conceptos
//  Se toma como base la tabla cat_tipo_nomina de pronomina y se actualiza catalogos
//  mysql	
////////////////////////////////////////////////////////////////////////



?>		        