<?php

include "./general/DBC.php";
include "./general/generales.inc";

$db = new DbCnnx();    

$method = "";
if(isset($_SERVER['REQUEST_METHOD']))
	$method = $_SERVER['REQUEST_METHOD'];

if ( $method == "POST") {
	$Usuario="xxx";
	if(isset($_POST['inputUsuario']))
		$Usuario=$_POST['inputUsuario'];
	$Passwd="xxx";
	if(isset($_POST['inputPassword']))
		$Passwd=$_POST['inputPassword'];
	$Privilegio="";
	if(isset($_POST['inputPrivilegio']))
		$Passwd=$_POST['inputPrivilegio'];

	$SQL = "SELECT 'POST', usu.nombre as nombre_usuario,usu.app_paterno, 
		usu.app_materno, pri.id_roles, rol.descripcion, org.id, org.nombre as organismo
		FROM usuarios usu, privilegios pri, organismos org, roles rol
		WHERE usu.id=pri.id_usuarios AND pri.id_organismos= org.id AND 
		pri.id_roles= rol.id AND 
		usu.id='" . $Usuario ."' AND usu.password='" . $Passwd."'  AND pri.estatus='A'";

}
elseif( $method == "GET") {
session_start();	
	$Usuario="xxx";
	if(isset($_SESSION['inputUsuario']))
		$Usuario=$_SESSION['inputUsuario'];
	$Passwd="xxx";
	if(isset($_SESSION['inputPassword']))
		$Passwd=$_SESSION['inputPassword'];

	$Privilegio="";
	if(isset($_GET['inputPrivilegio']))
		$Privilegio=$_GET['inputPrivilegio'];

	$SQL = "SELECT 'GET', usu.nombre as nombre_usuario,usu.app_paterno, usu.app_materno, 
		pri.id_roles, rol.descripcion, org.id, org.nombre as organismo
		FROM usuarios usu, privilegios pri, organismos org, roles rol
		WHERE usu.id=pri.id_usuarios AND pri.id_organismos= org.id AND 
		pri.id_roles= rol.id AND 
		usu.id='" . $Usuario ."' AND usu.password='" . $Passwd."'  AND pri.estatus='A' AND
		pri.id_roles='$Privilegio'";
}
else{
	echo "Metodo de Requerimento Desconocido <br>";
}

//echo "Usuario >$Usuario< Passwd >$Passwd< <br>";
//$Usuario = $db->quote($Usuario);
//$Passwd = $db->quote($Passwd);


echo "SQL II >$SQL< <br>";



//$rows = $db->select($SQL);
//echo "error >>" .$db->error()."< <br>" ;

//if(!$rows)
if(false)	
	header("location: index.php?msg=Credenciales no Autorizadas ");
else
{
	echo "Si encontro registrs <bR>";
	session_start();
    $_SESSION = $_POST;
    //session_write_close();
	$Contador=  CERO;
	$Menu="";
	
	while(isset($rows[$Contador]['nombre_usuario']))
	{
		$_SESSION['idorg'] = $rows[$Contador]['id'];
		$_SESSION['organismo'] = $rows[$Contador]['organismo'];
		echo "id >>" .$rows[$Contador]['id'] ." << <br>" ;

		$NombreUsuario = $rows[$Contador]['nombre_usuario'] . " " . $rows[$Contador]['app_paterno'] . " ". $rows[$Contador]['app_materno'];
		$Organismo = $rows[$Contador]['organismo'];
		if($Contador == CERO)
			$MenuOperacion =$rows[$Contador]['id_roles'];
		else
			$MenuOperacion =$MenuOperacion . "|" . $rows[$Contador]['id_roles'];		
		$Contador++;
	}// fin del while 
	
	$_SESSION['nombre_usuario'] ="noe" ;// $NombreUsuario;
	// menu_operacion solo identifica los menus que va desplegar en la barra lateral


	$_SESSION['menu_operacion'] = "1"; //$MenuOperacion;
	$_SESSION['modalidad'] = "inicial";
	
	//echo "MenuOperacion >>$MenuOperacion<< <br>";

	//break;
	//$ArrMenuOperacion = explode ("|", $MenuOperacion);
	//$NumPerfiles = count($ArrMenuOperacion);
	$MenuOperacion="1|2";
	$MenuOperacion=TRES;
	if($MenuOperacion == TRES)
		header("location: ptma_opcd/ptfma_admin.php");				
	elseif((int)$MenuOperacion === PRODUCTO_NOMINA and $NumPerfiles == UNO)
		header("location: ptma_opcd/ptfma_producto.php");	
	elseif($MenuOperacion == ART74){
		//header("location: ptma_opcd/ptfma_art74.php");	
		header("location: ptma_opcd/ptfma_trabajando.php");	
	}	
	elseif($MenuOperacion == ART74FII){
		//header("location: ptma_opcd/ptfma_art74f2.php");	
		header("location: ptma_opcd/ptfma_trabajando.php");	
	}	
	elseif($MenuOperacion == ART74FIII){
		header("location: ptma_opcd/ptfma_trabajando.php");	
		//header("location: ptma_opcd/ptfma_art74f3.php");	
	}	
	elseif($MenuOperacion == "1|2")	
		header("location: ptma_opcd/ptma_opcd.php");
	elseif(is_array($ArrMenuOperacion))	{
		$_SESSION['perfiles']      = $MenuOperacion;	
		$_SESSION['inputUsuario']  = $Usuario;
		$_SESSION['inputPassword'] = $Passwd;
		header("location: ptfma_multi_perfil.php");
	}	
	else	
		header("location: index.php?msg=Credenciales no Definidas  ");
}// if(!$rows)

?>