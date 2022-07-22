<?php
session_start();
include "../general/DBC.php";
include "../general/generales.inc";
include "ptma_opcd.inc";
include "ptfma_admin.inc";

$db=new DbCnnx();
$contador=CERO;
$Qna='';
$Anio='';
$fecha_limite='';
$QnaMax='';

if(isset($_GET['anio'])&&isset($_GET['Qna'])){
	$anio=$_GET['anio'];
	$Qna=$_GET['Qna'];
	$SQLPeriodo_Atrasado="SELECT numero as num_quincena,anio,MAX(fecha_envio)as fecha_limite,MAX(numero)as max_quincena 
	FROM periodos 
	WHERE anio=$anio AND numero=$Qna";
	
	//echo $SQLPeriodo_Atrasado;

	$Rows=$db->select($SQLPeriodo_Atrasado);
	if(!$Rows){
	echo 'error de consulta';
	}else{
		if(is_array($Rows)){
			$Qna=$Rows[$contador]['num_quincena'];
			$Anio=$Rows[$contador]['anio'];
			$fecha_limite=$Rows[$contador]['fecha_limite'];
			$QnaMax=$Rows[$contador]['max_quincena'];
		}
	
	}


}else{
	$SQLPeriodo="SELECT MIN(anio) as anio,
	MIN(numero) AS num_quincena,MIN(fecha_envio) AS fecha_limite,
	MAX(numero) AS max_quincena,MAX(fecha_envio) AS max_limite 
	FROM periodos
	WHERE fecha_envio > CURDATE();";

	$Rows=$db->select($SQLPeriodo);
	if(!$Rows){
	echo 'error de consulta';
	}else{
		if(is_array($Rows)){
			$Qna=$Rows[$contador]['num_quincena'];
			$Anio=$Rows[$contador]['anio'];
			$fecha_limite=$Rows[$contador]['fecha_limite'];
			$QnaMax=$Rows[$contador]['max_quincena'];
		}
		
		
}
}
$JS = fncBuildJSAdmin();
	echo fncBuildHead();
	echo fncBuildBodyAdmin($Qna,$Anio,$fecha_limite,$QnaMax);
	echo fncBuildTail($JS);

?>


