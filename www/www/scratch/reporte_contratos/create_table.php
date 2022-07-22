<?php

echo "drop table reporte_contratos_final; <br>";
echo "create  table reporte_contratos_final <br>";
echo "( anio_qna_ini varchar(7), <br>
	estado varchar(2), <br>";
echo "rfc varchar(15), <br>";
echo "curp varchar(25), <br>";
echo "nombre varchar(150), <br>";

for($Ind=16; $Ind<25;$Ind++)
	echo "A13_".$Ind."  varchar(15), <br>";
for($Ind=1; $Ind<25;$Ind++)
	echo "A14_".$Ind."  varchar(15), <br>";

for($Ind=1; $Ind<25;$Ind++)
	echo "A15_".$Ind."  varchar(15), <br>";

for($Ind=1; $Ind<25;$Ind++)
	echo "A16_".$Ind."  varchar(15), <br>";

echo "); <br>";

echo "OPTIONS (ERRORS=1) <br>";
echo "LOAD DATA <br>";
echo "INFILE 'file.load' <br>";
echo "APPEND<br>";
echo "INTO TABLE \"PRO_NOMINA\".\"REPORTE_CONTRATOS_FINAL\" <br>";
echo "FIELDS TERMINATED BY '|'<br>";
echo "OPTIONALLY ENCLOSED BY '\"' AND '\"' <br>";
echo "TRAILING NULLCOLS ( <br>";
echo "estado , <br>";
echo "rfc , <br>";
for($Ind=16; $Ind<25;$Ind++)
	echo "A13_".$Ind."  , <br>";
for($Ind=1; $Ind<25;$Ind++)
	echo "A14_".$Ind."  , <br>";

for($Ind=1; $Ind<25;$Ind++)
	echo "A15_".$Ind."  , <br>";

for($Ind=1; $Ind<25;$Ind++)
	echo "A16_".$Ind."  , <br>";

echo "); <br>";



?>