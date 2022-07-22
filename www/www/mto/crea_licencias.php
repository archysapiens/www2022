<?php

;###############################################
; Secretaria de Salud
; Archivo de Generacion de Licencias de Uso.
; Fecha:28-Nov-2016
; 
;###############################################

include "../general/DBC.php";
include "../general/generales.inc";
for($i=1; $i<100;$i++){
	$Ind = str_pad($i,2,"0", STR_PAD_LEFT);

	$Lic = 'SSA_'.$Ind.strtoupper(uniqid(rand()));
	echo $Ind."-->".$Lic ."<br>";
	

$db = new DbCnnx();   
$SQLRemesas =" INSERT INTO licencias
            (id,
             numero_licencia,
             fecha_ini_vigencia,
             fecha_fin_vigencia,
             estatus,
             comentarios)
		VALUES ($i,
		        '$Lic',
		        now(),
		        NOW() + INTERVAL 400 DAY,
		        'A',
		        '')	";
$rows = $db->select($SQLRemesas);	

}	



?>