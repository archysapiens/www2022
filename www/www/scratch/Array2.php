<?php


for($i=0; $i<10; $i++)
	for($j=0; $j<10; $j++){
		
		$ArrMult['A1'][$i] =$i*$j;
	}

for($i=0; $i<10; $i++)
	for($j=0; $j<10; $j++){
		$Elemento=array($i,$j);
		$ArrMult['A2'][$i] =$i*$i;
	}

//print_r($ArrMult['A1']);

//print_r($ArrMult);

foreach ($ArrMult as $key => $value ) {

//echo $key ;
//echo "  " ;
//echo (int)$value;
//print_r($value);
//echo "<br>";

foreach($value as $data => $user_data)    {
            echo "Array number: $key, contains $data with $user_data.  <br>";
        }

}



?>