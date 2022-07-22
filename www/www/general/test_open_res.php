<?php

$IdArchivoSQLRespuesta="mid_res.txt";

$myfile = fopen($IdArchivoSQLRespuesta, "r") or die("Unable to open file!".$IdArchivoSQLRespuesta);
$Respuesta[]=array();

   //  Output one line until end-of-file
	$contador=0;
	while(!feof($myfile)) {
    	$StrPaso = fgets($myfile);

    	echo "StrPaso >>$StrPaso<<  <br>";
    	if($contador==0){
    		echo "Una vez <br>";
    		$ArrayLlaves= explode("|",$StrPaso);
    		
    	}
    	else{
    		$Llave1=preg_replace('/[^A-Za-z0-9\-]/', '',$ArrayLlaves[0]);
    		$ArrRegistro= explode("|",$StrPaso);
    		
    		$Respuesta[$Llave1][$contador] = preg_replace('/[^A-Za-z0-9\-]/', '',($ArrRegistro[0]));
    		$Llave2=preg_replace('/[^A-Za-z0-9\-]/', '',$ArrayLlaves[1]);
    		if(isset($ArrRegistro[1]))
    			$Respuesta[$Llave2][$contador] = preg_replace('/[^A-Za-z0-9\-]/', '',($ArrRegistro[1]));
    		else
    			$Respuesta[$Llave2][$contador] ="";
    	}
    	$contador++;
	}// fin del while



foreach ($Respuesta as &$valor) {
    //$Str =$valor[1]['UR'];
    echo "Valor <br>";
  print_r($valor);
    echo "<br>";
  //  echo " Str >>$Str<< <br>";
}
$contador=1;
while($Respuesta['UR'][$contador]){

	echo "UR >".$Respuesta['UR'][$contador] ." DESC ".$Respuesta['DESCRIPCION'][$contador]."<br>";

$contador++;
}

echo "Array Completo <br><br>";

	print_r($Respuesta);

?>