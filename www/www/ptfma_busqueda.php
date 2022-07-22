<?php
include "./general/DBC.php";
include "./general/generales.inc";
$db       =new DbCnnx();
/*
 * IMPLEMENTACION DE LA BUSQUEDA DE LA PREGUNTA ATRAVES DEL CORREO
 */
	$email=$_POST['parametro'];

if(isset($email)){
	
	$Consulta_pregunta="SELECT distinct pregunta.pregunta as pre FROM pregunta,usuarios WHERE usuarios.id='".$email."' AND pregunta.id=usuarios.pregunta;";
	$Rows = $db->select($Consulta_pregunta);
	
	if(!$Rows){

		echo 'Error de correo';

	}else{

		$Contador=CERO;

		if(is_array($Rows)){
	
			$Password  = $Rows[$Contador]['pre'];
			echo utf8_encode($Password);

		}
	}
 }

?>
