<?php

$PerIni="20160927";
$PerFin="20160927";
echo ">>".substr($PerFin,0,4)."<<";


$LocCampo ="2016";
	if (strlen($LocCampo) == 4){
		if((int)$LocCampo > (int)substr($PerIni,0,4) OR 
					(int)$LocCampo > (int)substr($PerFin,0,4)){
			$Error = "1" ."|"."error"."|".$LocCampo."|" . "Erro desc "."|<br>";
			echo $Error;
			$Bandera = 1;
		}
	}
	
?>