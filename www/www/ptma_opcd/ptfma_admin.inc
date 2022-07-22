<?php

function fncIntegraTablaResumen($Qna,$Anio)
{
    
$db = new DbCnnx(); 
$R416[50]='';
$P416[31]='';
$D416[31]='';
$T416[31]='';
$P610[31]='';       
$D610[31]='';       
$T610[31]='';      
$PX00[31]='';
$DX00[31]='';
$TX00[31]='';
$tabla[31]=0;
$EX00[31]='';
$E610[31]='';
$E416[31]='';
$ORGX[31]='';
$ORG4[31]='';
$ORG6[31]='';
$UX00[31]='';
$U610[31]='';
$U416[31]='';
$FX00[31]='';
$F415[31]='';
$F610[31]='';
$fecha4="";
$fechax="";
$fecha6="";
$ur='';
$i=0;
$Estados_terminados=0;
$color='';
$tipo='';

$SQL_X00_cuenta="SELECT count(percepciones) as numx from log_carga inner join remesas on remesas.id=log_carga.id_remesas where numero_periodos='".$Qna."' and anio_periodos=2016 and ur='X00'";
$SQL_416_cuenta="SELECT count(percepciones) as num4 from log_carga inner join remesas on remesas.id=log_carga.id_remesas where numero_periodos='".$Qna."' and anio_periodos=2016 and ur='416'";
$SQL_610_cuenta="SELECT count(percepciones) as num6 from log_carga inner join remesas on remesas.id=log_carga.id_remesas where numero_periodos='".$Qna."' and anio_periodos=2016 and ur='610'";

$SQL_X00="SELECT estatus,percepciones,deducciones,(Percepciones+Deducciones) as SumaX, nombre,id_usuarios,remesas.fecha_actualizacion as FX00
    FROM log_carga inner join remesas inner join organismos on organismos.id=remesas.id_organismos and log_carga.id_remesas=remesas.id 
    WHERE ur='X00' and numero_periodos='".$Qna."' and anio_periodos='".$Anio."' order by id_usuarios";    
$SQL_416="SELECT estatus,percepciones,deducciones,(Percepciones+Deducciones) as Suma4, nombre,id_usuarios,remesas.fecha_actualizacion as F416
    FROM log_carga inner join remesas inner join organismos on organismos.id=remesas.id_organismos and log_carga.id_remesas=remesas.id 
    WHERE ur='416' and numero_periodos='".$Qna."' and anio_periodos='".$Anio."' order by id_usuarios";    
$SQL_610="SELECT estatus,percepciones,deducciones,(Percepciones+Deducciones) as Suma6, nombre,id_usuarios,remesas.fecha_actualizacion as F610
    FROM log_carga inner join remesas inner join organismos on organismos.id=remesas.id_organismos and log_carga.id_remesas=remesas.id 
    WHERE ur='610' and numero_periodos='".$Qna."' and anio_periodos='".$Anio."' order by id_usuarios";    
$Rowsx=$db->select($SQL_X00);
$Rows4=$db->select($SQL_416);
$Rows6=$db->select($SQL_610);
$RowsX_cuenta=$db->select($SQL_X00_cuenta);
$Rows4_cuenta=$db->select($SQL_416_cuenta);
$Rows6_cuenta=$db->select($SQL_610_cuenta);
$Contador=CERO;
$NumX="";
    if(!$Rowsx&&!$RowsX_cuenta){
        $NumX=0;
    echo "no arrojo nada X00";
    }else{
      
          while(isset($Rowsx[$Contador]['percepciones'])){
            $PX00[$Contador] =$Rowsx[$Contador]['percepciones'];
            $DX00[$Contador] =$Rowsx[$Contador]['deducciones'];
            $SX00[$Contador] =$Rowsx[$Contador]['SumaX'];
            $ORGX[$Contador] =$Rowsx[$Contador]['nombre'];
            $FX00[$Contador] =$Rowsx[$Contador]['FX00'];
            $UX00[$Contador] =$Rowsx[$Contador]['id_usuarios'];
            $EX00[$Contador] =$Rowsx[$Contador]['estatus'];
            $FX00[$Contador] =$Rowsx[$Contador]['FX00'];

           //echo $Contador." ".$PX00[$Contador].$DX00[$Contador].$SX00[$Contador].$ORGX[$Contador]."X00 <br>";
        //echo $PX00[$Contador].$ORGX[$Contador]."<br>";
           $Contador++;
           
          }//fin primer while
          $Contador=CERO;
          while(isset($RowsX_cuenta[$Contador]['numx'])){
           $NumX=$RowsX_cuenta[$Contador]['numx'];
           //echo $NumX."numero";
           $Contador++;
          }//fin segundo wuile
      
      
    }//fin del else
    
    $Contador=CERO;
    if(!$Rows4&&!$Rows4_cuenta){
        $Num4=0;
        echo "no arrojo nada 416";
    }else{
      while(isset($Rows4[$Contador]['percepciones'])){
        $P416[$Contador]=$Rows4[$Contador]['percepciones'];
        $D416[$Contador]=$Rows4[$Contador]['deducciones'];
        $S416[$Contador]=$Rows4[$Contador]['Suma4'];
        $ORG4[$Contador]=$Rows4[$Contador]['nombre'];
        $F416[$Contador]=$Rows4[$Contador]['F416'];
        $U416[$Contador] =$Rows4[$Contador]['id_usuarios'];
        $E416[$Contador] =$Rows4[$Contador]['estatus'];
        $F416[$Contador] =$Rows4[$Contador]['F416'];
       //echo $Contador." ".$P416[$Contador].$D416[$Contador].$S416[$Contador].$ORG4[$Contador]."416<br>";
      
       $Contador++;
      }//fin primer while
      $Contador=CERO;
      while(isset($Rows4_cuenta[$Contador]['num4'])){
        $Num4=$Rows4_cuenta[$Contador]['num4'];
       // echo $Num4;
       $Contador++;
      }//fin segundo wuile
    }//fin del if

    $Contador=CERO;
    if(!$Rows6&&$Rows6_cuenta){
        $Num6=0;
    echo "no arrojo nada 610 ".$Num6;
    }else{
      while(isset($Rows6[$Contador]['percepciones'])){
        $P610[$Contador]=$Rows6[$Contador]['percepciones'];
        $D610[$Contador]=$Rows6[$Contador]['deducciones'];
        $S610[$Contador]=$Rows6[$Contador]['Suma6'];
        $ORG6[$Contador]=$Rows6[$Contador]['nombre'];
        $F610[$Contador]=$Rows6[$Contador]['F610'];
        $U610[$Contador] =$Rows6[$Contador]['id_usuarios'];
        $E610[$Contador] =$Rows6[$Contador]['estatus'];
        $F610[$Contador] =$Rows6[$Contador]['F610'];
        //echo $Contador." ".$P610[$Contador].$D610[$Contador].$S610[$Contador].$ORG6[$Contador]."610<br>";

       $Contador++;
      }//fin primer while
      $Contador=CERO;
      while(isset($Rows6_cuenta[$Contador]['num6'])){
       $Num6=$Rows6_cuenta[$Contador]['num6'];
       //echo $Num6;
       $Contador++;
      }//fin segundo wuile
    }//fin del if


//AQUI EMPIEZAN LOS COMPARADORES
$Percepciones_X[500]="";
if($NumX>=$Num4&&$NumX>=$Num6){
$Percepciones_X[$NumX]="";
$Deducciones_X[$NumX]  ="";
$Percepciones_6[$NumX]="";
$Deducciones_6[$NumX]  ="";
$Percepciones_4[$NumX]="";
$Deducciones_4[$NumX]  ="";
$Total_x[$NumX]="";
$Total_6[$NumX]="";
$Total_4[$NumX]="";
$organismos[$NumX]="";
$usuarios[$NumX]="";
$Status_x[$NumX]="";
$Status_4[$NumX]="";
$Status_6[$NumX]="";
$Fecha_x[$NumX]="";
$Fecha_4[$NumX]="";
$Fecha_6[$NumX]="";

//echo "X es el mayor ".$NumX." for1"."<br>";
    
    for ($i=0; $i <$NumX ; $i++) { 
        //echo "Percepciones X00 ".$PX00[$i]."Deducciones X00 ".$DX00[$i].$ORGX[$i]." A <br>";
        $Percepciones_X[$i]=$PX00[$i];
        $Deducciones_X[$i]=$DX00[$i];
        $Total_x[$i]=$SX00[$i];
        $organismos[$i]=$ORGX[$i];
        $usuarios[$i]=$UX00[$i];
        $Status_x[$i]=$EX00[$i];
        $Fecha_x[$i]=$FX00[$i];
        if($Num4>0){
            /////////////////
            if($Num4>=$Num6){
                for ($j=0; $j <$Num4; $j++) { 
                    if($ORGX[$i]==$ORG4[$j]){
                        //echo "Percepciones 416 ".$P416[$j]."Deducciones 416".$D416[$j].$ORG4[$j]." Q <br>";
                        $Percepciones_4[$i]=$P416[$j];
                        $Deducciones_4[$i]=$D416[$j];
                        $Total_4[$i]=$S416[$j];
                        $Status_4[$i]=$E416[$j];
                        $Fecha_4[$i]=$F416[$i];
                        //echo $Deducciones_4[$i].$Percepciones_4[$i];
                        if($Num6>0){
                            for ($k=0; $k <$Num6; $k++) { 
                                if($ORG6[$k]==$ORG4[$j]){
                                    //echo "Percepciones 610 ".$P610[$k]."Deducciones 610 ".$D610[$k].$ORG6[$k]." U<br>";
                                    $Percepciones_6[$i]=$P610[$k];
                                    $Deducciones_6[$i]=$D610[$k];
                                    $Total_6[$i]=$S610[$k];
                                    $Status_6[$i]=$E610[$k];
                                    $Fecha_6[$i]=$F610[$k];
                                }
                            }//Fin for k
                        }else{  
                            //echo "NUMERO ".$Num6." NUMERO";
                                    $Percepciones_6[$i]=0;
                                    $Deducciones_6[$i]=0;
                                    $Total_6[$i]=0;
                                    $Status_6[$i]=0;
                                    $Fecha_6[$i]=0;
                        }//fin else 610
                     }//fin del if compara organismos
                }//fin del for 416

            }else if($Num6>$Num4){//fin del if 416>610
                for ($j=0; $j <$Num6 ; $j++) { 
                    if($ORGX[$i]==$ORG6[$j]){
                       // echo "Percepciones 610 ".$P610[$j]."Deducciones 610 ".$D610[$j].$ORG6[$j]." I <br>";
                        $Percepciones_6[$i]=$P610[$j];//
                        $Deducciones_6[$i]=$D610[$j];
                        $Total_6[$i]=$S610[$j];
                        $Status_6[$i]=$E610[$j];
                        $Fecha_6[$i]=$F610[$j];
                        if($Num4>0){
                            for ($k=0; $k <$Num4 ; $k++) { 
                                if($ORG6[$j]==$ORG4[$k]){
                                    //echo "Percepciones 416 ".$P416[$k]."Deducciones 416 ".$D416[$k].$ORG4[$k]." E <br>";
                                    $Percepciones_4[$i]=$P416[$k];
                                    $Deducciones_4[$i]=$D416[$k];
                                    $Total_4[$i]=$S416[$k];
                                    $Status_4[$i]=$E416[$k];
                                    $Fecha_4[$i]=$F416[$k];
                                    //echo $Deducciones_4[$i].$Percepciones_4[$i];
                                }//fin del if compara organismos en 610 y 416
                            }//fin del for del 416
                        }else{
                                    $Percepciones_4[$i]="0";
                                    $Deducciones_4[$i]="0";
                                    $Total_4[$i]="0";
                                    $Status_4[$i]="0";
                                    $Fecha_4[$i]="0";
                                    //echo $Deducciones_4[$i].$Percepciones_4[$i];

                        }//fin del esle 416=0
                    }//fin del if compara organismos X00 y 610
                }
            }//fin del else
            ////////////
            
        }else if($Num6>0){
            for ($j=0; $j <$Num6; $j++) { 
                if($ORG6[$j]==$ORGX[$i]){
                    //echo $P610[$j].$D610[$j];

                }
            }
        }else if($Num4==0&&$Num6==0){
            $Num6=0;
            $Num4=0;
            $Percepciones_4[$i]="0";
            $Percepciones_6[$i]="0";
            $Deducciones_4[$i]="0";
            $Deducciones_6[$i]="0";
            $Status_4[$i]="0";
            $Status_6[$i]="0";
            $Fecha_4[$i]="0";
            $Fecha_6[$i]="0";
        }//fin del else

    }//fin del for i
    for ($i=0; $i <$NumX ; $i++) { 
        
        $org=str_replace(" ", "_", $organismos[$i]);
        if(isset($Fecha_6[$i])){
                    $fecha6=$Fecha_6[$i];

                }else{
                    $fecha6="0000-00-00";
                }
                if(isset($Fecha_4[$i])){
                    $fecha4=$Fecha_4[$i];
                }else{
                    $fecha4="0000-00-00";
                }
                if(isset($Fecha_x[$i])){
                    $fechax=$Fecha_x[$i];
                }else{
                    $fechax="0000-00-00";
          }//fin de comparacion de fechas

        if(isset($usuarios[$i])){
            $usuarios[$i]=$usuarios[$i];

        }else{
            $usuarios[$i]="0";
        }
        if(isset($Status_x[$i])){
            if($Status_x[$i]=="T"){
                    $color='label label-success';
                    $tipo='Terminado';
            }else if($Status_x[$i]="A"){
                    $color='label label-primary2';
                    $tipo='Actualizado';
            }
        }elseif (isset($Status_4[$i])) {
          if($Status_4[$i]=="T"){
                    $color='label label-success';
                    $tipo='Terminado';
            }else if($Status_4[$i]="A"){
                    $color='label label-primary2';
                    $tipo='Actualizado';
            }
        }elseif (isset($Status_6[$i])) {
          if($Status_6[$i]=="T"){
                    $color='label label-success';
                    $tipo='Terminado';
            }else if($Status_6[$i]="A"){
                    $color='label label-primary2';
                    $tipo='Actualizado';
            }
        }

        
echo $tabla= "
  <table class=\"table table-hover\">
       <tbody>
                                    <tr>
                                        <td class=\"project-status\"width=\"50\">
                                            <span class=\"$color\">$tipo</span>
                                        </td>
                                        <td class=\"project-title\"width=\"125\">
                                            <a href=\"organismo=".$usuarios[$i]."&estado=".$org."\" id=\"organismo$i\">";if(isset($organismos[$i])){echo$organismos[$i];}else{echo "Nada";}echo"</a>
                                           <br>
                                            <small>Act.";echo fechas($fechax,$fecha4,$fecha6);echo"</small>
                                        </td>
                                        
                                        
                                        <td class=\"project-completion\" width=\"130\">
                                          <strong>416$ ";if(isset($Total_4[$i])){echo $Total_4[$i];}else{echo "0";} echo "</strong>
                                          <div>   
                                              <small> Perc.: $";if(isset($Percepciones_4[$i])){echo $Percepciones_4[$i];}else{echo "0";} echo"</small><br>
                                              <small> Dedu.: $";if(isset($Deducciones_4[$i])){echo $Deducciones_4[$i];}else{echo "0";} echo"</small>
                                          </div>
                                        </td>

                                      

                                        <td class=\"project-completion\" width=\"130\">
                                              <strong> X00 $";if(isset($Total_x[$i])){echo $Total_x[$i];}else{echo "0";}echo" </strong>
                                                 <div>   
                                                <small> Perc.: $";if(isset($Percepciones_X[$i])){echo $Percepciones_X[$i];}else{echo "0";}echo" </small><br>
                                              <small> Dedu.: $"; if(isset($Deducciones_X[$i])){echo $Deducciones_X[$i];}else{echo "0";}echo" </small>
                                                </div>
                                        </td>
                                        <td class=\"project-completion\" width=\"130\">
                                              <strong> 610 $";if(isset($Total_6[$i])){echo $Total_6[$i];}else{echo "0";}echo"</strong>
                                             <div>   
                                                 <small> Perc.: $"; if(isset($Percepciones_6[$i])){echo $Percepciones_6[$i];}else{echo "0";}echo" </small><br>
                                              <small> Dedu.: $"; if(isset($Deducciones_6[$i])){echo $Deducciones_6[$i];}else{echo "0";}echo" </small>
                                             </div>
                                        </td>
                                        <td class=\"project-people\"width=\"170\">
                                              <a id=\"view-pdf1\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf2\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>

                                              <a id=\"view-pdf3\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.jpg\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>
                                        </td>
                                        <td class=\"project-actions\" width=\"100\">
                                            <a id=\"timeline\" href=\"ptfma_timeline.php?id=".$org."\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x \"></i></a>
                                        </td>
                                    </tr>
                                    
                                    </tbody>
                                </table>";        


                              }//fin del for que crea la tabla

echo "<div class=\"numero_mayor\" id='$Num6'></div>";//este div es para el scrip que manda a traer ptfma_envia_remesa_info.php

}else if($Num4>=$NumX&&$Num4>=$Num6){
$Percepciones_X[$Num4]="";
$Deducciones_X[$Num4]  ="";
$Percepciones_6[$Num4]="";
$Deducciones_6[$Num4]  ="";
$Percepciones_4[$Num4]="";
$Deducciones_4[$Num4]  ="";
$Total_x[$Num4]="";
$Total_6[$Num4]="";
$Total_4[$Num4]="";
$organismos[$Num4]="";
$usuarios[$Num4]="";
$Status_x[$Num4]="";
$Status_4[$Num4]="";
$Status_6[$Num4]="";
$Fecha_4[$Num4]="";
$Fecha_6[$Num4]="";
$Fecha_x[$Num4]="";

//echo "4 es el mayor ".$Num4." for2"."<br>";
    for ($i=0; $i <$Num4 ; $i++) { 
       // echo $i." ".$P416[$i].$ORG4[$i]."Percepciones 4 <br>";
//echo "Percepciones 416 ".$P416[$i]."Deducciones 416 ".$D416[$i].$ORG4[$i]." A <br>";
        $Percepciones_4[$i]=$P416[$i];
        $Deducciones_4[$i]=$D416[$i];
        $organismos[$i]=$ORG4[$i];
        $usuarios[$i]=$U416[$i];
        $Status_4[$i]=$E416[$i];
        $Fecha_4[$i]=$F416[$i];

        if(isset($S416[$i])){
            $Total_4[$i]=$S416[$i];
        }
        
        if($NumX>0){
            /////////////////
            if($NumX>=$Num6){
                for ($j=0; $j <$NumX; $j++) { 
                    if($ORG4[$i]==$ORGX[$j]){
                        //echo "Percepciones X00 ".$PX00[$j]."Deducciones X00".$X00[$j].$ORGX[$j]." Q <br>";
                        $Percepciones_X[$i]=$PX00[$j];
                        $Deducciones_X[$i]=$DX00[$j];
                        $Total_x[$i]=$SX00[$j];
                        $Status_x[$i]=$EX00[$j];
                        $Fecha_x[$i]=$FX00[$j];
                        //echo $Deducciones_x[$i].$Percepciones_X[$i];
                        if($Num6>0){
                            for ($k=0; $k <$Num6; $k++) { 
                                if($ORG6[$k]==$ORG4[$j]){
                                    //echo "Percepciones 610 ".$P610[$k]."Deducciones 610 ".$D610[$k].$ORG6[$k]." U<br>";
                                    $Percepciones_6[$i]=$P610[$k];
                                    $Deducciones_6[$i]=$D610[$k];
                                    $Total_6[$i]=$S610[$k];
                                    $Status_6[$i]=$E610[$k];
                                    $Fecha_6[$i]=$F610[$k];
                                }
                            }//Fin for k
                        }else{  
                            //echo "NUMERO ".$Num6." NUMERO";
                                    $Percepciones_6[$i]=0;
                                    $Deducciones_6[$i]=0;
                                    $Total_6[$i]=0;
                                    $Status_6[$i]=0;   
                                    $Fecha_6[$i]=0;
                        }//fin else 610
                     }//fin del if compara organismos
                }//fin del for 416

            }else if($Num6>$NumX){//fin del if 416>610
                for ($j=0; $j <$Num6 ; $j++) { 
                    if($ORG4[$i]==$ORG6[$j]){
                        //echo "Percepciones 610 ".$P610[$j]."Deducciones 610 ".$D610[$j].$ORG6[$j]." I <br>";
                        $Percepciones_6[$i]=$P610[$j];
                        $Deducciones_6[$i]=$D610[$j];
                        $Total_6[$i]=$S610[$j];
                        $Status_6[$i]=$E610[$j];
                        $Fecha_6[$i]=$F610[$j];
                        if($NumX>0){
                            for ($k=0; $k <$NumX ; $k++) { 
                                if($ORG6[$j]==$ORGX[$k]){
                                    //echo "Percepciones X00 ".$PX00[$k]."Deducciones X00 ".$DX00[$k].$ORGX[$k]." E <br>";
                                    $Percepciones_X[$i]=$PX00[$k];
                                    $Deducciones_X[$i]=$DX00[$k];
                                    $Total_x[$i]=$SX00[$k];
                                    $Status_x[$i]=$EX00[$k];
                                    $Fecha_x[$i]=$FX00[$k];
                                    //echo $Deducciones_4[$i].$Percepciones_4[$i];
                                }//fin del if compara organismos en 610 y 416
                            }//fin del for del 416
                        }else{
                                    $Percepciones_X[$i]="0";
                                    $Deducciones_X[$i]="0";
                                    $Total_x[$i]="0";
                                    $Status_x[$i]="0";
                                    $Fecha_x[$i]="0";
                                    //echo $Deducciones_4[$i].$Percepciones_4[$i];

                        }//fin del esle 416=0
                    }//fin del if compara organismos X00 y 610
                }
            }//fin del else
            ////////////
            
        }else if($Num6>0){
            for ($j=0; $j <$Num6; $j++) { 
                if($ORG6[$j]==$ORGX[$i]){
                    //echo $P610[$k].$D610[$k];

                }
            }
        }else if($NumX==0&&$Num6==0){
            $Num6=0;
            $NumX=0;
            $Percepciones_X[$i]="0";
            $Percepciones_6[$i]="0";
            $Deducciones_X[$i]="0";
            $Deducciones_6[$i]="0";
            $Total_x[$i]="0";
            $Total_6[$i]="0";
            $Status_x[$i]="0";
            $Status_6[$i]="0";
            $Fecha_x[$i]="0";
            $Fecha_6[$i]="0";
        }//fin del else
    }//fin del for i
    //echo $Num4;
    for ($i=0; $i <$Num4 ; $i++) { 
                $org=str_replace(" ", "_", $organismos[$i]);
                
                 if(isset($Fecha_6[$i])){
                    $fecha6=$Fecha_6[$i];

                }else{
                    $fecha6="0000-00-00";
                }
                if(isset($Fecha_4[$i])){
                    $fecha4=$Fecha_4[$i];
                }else{
                    $fecha4="0000-00-00";
                }
                if(isset($Fecha_x[$i])){
                    $fechax=$Fecha_x[$i];
                }else{
                    $fechax="0000-00-00";
                }

                if(isset($usuarios[$i])){
                    $usuarios[$i]=$usuarios[$i];

                }else{
                    $usuarios[$i]="0";
                }
                
                if(isset($Status_x[$i])){
            if($Status_x[$i]=="T"){
                    $color='label label-success';
                    $tipo='Terminado';
            }else if($Status_x[$i]="A"){
                    $color='label label-primary2';
                    $tipo='Actualizado';
            }
        }elseif (isset($Status_4[$i])) {
          if($Status_4[$i]=="T"){
                    $color='label label-success';
                    $tipo='Terminado';
            }else if($Status_4[$i]="A"){
                    $color='label label-primary2';
                    $tipo='Actualizado';
            }
        }elseif (isset($Status_6[$i])) {
          if($Status_6[$i]=="T"){
                    $color='label label-success';
                    $tipo='Terminado';
            }else if($Status_6[$i]="A"){
                    $color='label label-primary2';
                    $tipo='Actualizado';
            }
        }
echo $tabla= "
  <table class=\"table table-hover\">
       <tbody> 
                                    <tr>
                                        <td class=\"project-status\"width=\"50\">
                                            <span class=\"$color\">$tipo</span>
                                        </td>
                                        <td class=\"project-title\"width=\"130\">
                                            <a href=\"organismo=".$usuarios[$i]."&estado=".$org."\" id=\"organismo$i\">";if(isset($organismos[$i])){echo$organismos[$i];}else{echo "Nada";}echo"</a>
                                            <br>
                                            <small>Act.";echo fechas($fechax,$fecha4,$fecha6);echo"</small>
                                        </td>
                                        
                                        
                                        <td class=\"project-completion\" width=\"130\">
                                          <strong>416$ ";if(isset($Total_4[$i])){echo $Total_4[$i];}else{echo "0";} echo "</strong>
                                          <div>   
                                              <small> Perc.: $";if(isset($Percepciones_4[$i])){echo $Percepciones_4[$i];}else{echo "0";} echo"</small><br>
                                              <small> Dedu.: $";if(isset($Deducciones_4[$i])){echo $Deducciones_4[$i];}else{echo "0";} echo"</small>
                                          </div>
                                        </td>

                                      

                                        <td class=\"project-completion\" width=\"130\">
                                              <strong> X00 $";if(isset($Total_x[$i])){echo $Total_x[$i];}else{echo "0";}echo" </strong>
                                                 <div>   
                                                <small> Perc.: $";if(isset($Percepciones_X[$i])){echo $Percepciones_X[$i];}else{echo "0";}echo" </small><br>
                                              <small> Dedu.: $"; if(isset($Deducciones_X[$i])){echo $Deducciones_X[$i];}else{echo "0";}echo" </small>
                                                </div>
                                        </td>
                                        <td class=\"project-completion\" width=\"130\">
                                              <strong> 610 $";if(isset($Total_6[$i])){echo $Total_6[$i];}else{echo "0";}echo"</strong>
                                             <div>   
                                                 <small> Perc.: $"; if(isset($Percepciones_6[$i])){echo $Percepciones_6[$i];}else{echo "0";}echo" </small><br>
                                              <small> Dedu.: $"; if(isset($Deducciones_6[$i])){echo $Deducciones_6[$i];}else{echo "0";}echo" </small>
                                             </div>
                                        </td>
                                        <td class=\"project-people\"width=\"170\">
                                              <a id=\"view-pdf1\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf2\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>

                                              <a id=\"view-pdf3\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.jpg\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>
                                        </td>
                                        <td class=\"project-actions\" width=\"100\">
                                            <a id=\"timeline\" href=\"ptfma_timeline.php?id=".$org."\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x \"></i></a>
                                        </td>
                                    </tr>
                                    
                                    </tbody>
                                </table>";
        }//fin del for que crea la tabla
echo "<div class=\"numero_mayor\" id='$Num6'></div>";//este div es para el script que manda a traer ptfma_envia_remesa_info.php

}else if($Num6>=$NumX&&$Num6>=$Num4){
    $Percepciones_X[$Num6]="";
$Deducciones_X[$Num6]  ="";
$Percepciones_6[$Num6]="";
$Deducciones_6[$Num6]  ="";
$Percepciones_4[$Num6]="";
$Deducciones_4[$Num6]  ="";
$Total_x[$Num6]="";
$Total_6[$Num6]="";
$Total_4[$Num6]="";
$organismos[$Num6]="";
$usuarios[$Num6]="";
$Status_x[$Num6]="";
$Status_4[$Num6]="";
$Status_6[$Num6]="";
$Fecha_4[$Num6]="";
$Fecha_6[$Num6]="";
$Fecha_x[$Num6]="";

//echo "6 es el mayor ".$Num6." for3"."<br>";
    for ($i=0; $i <$Num6 ; $i++) { 

//echo "Percepciones 610 ".$P610[$i]."Deducciones 610 ".$D610[$i].$ORG6[$i]." A <br>";
        $Percepciones_6[$i] =$P610[$i];
        $Deducciones_6[$i]  =$D610[$i];
        $Total_6[$i]        =$S610[$i];
        $organismos[$i]     =$ORG6[$i];
        $usuarios[$i]       =$U610[$i];
        $Status_6[$i]       =$E610[$i];
        $Fecha_6[$i]        =$F610[$i];
        if($NumX>0){
            /////////////////
            if($NumX>=$Num4){
                for ($j=0; $j <$NumX; $j++) { 
                    if($ORG6[$i]==$ORGX[$j]){
                        //echo "Percepciones X00 ".$PX00[$j]."Deducciones X00".$DX00[$j].$ORGX[$j]." Q <br>";
                        $Percepciones_X[$i]=$PX00[$j];
                        $Deducciones_X[$i]=$DX00[$j];
                        $Total_x[$i]=$SX00[$j];
                        $Status_x[$i]=$EX00[$j];
                        $Fecha_x[$i]=$FX00[$j];
                        //echo $Deducciones_X[$i].$Percepciones_X[$i];
                        if($Num4>0){
                            for ($k=0; $k <$Num4; $k++) { 
                                if($ORG4[$k]==$ORGX[$j]){
                                    //echo "Percepciones 416 ".$P416[$k]."Deducciones 416 ".$D416[$k].$ORG4[$k]." U<br>";
                                    $Percepciones_4[$i]=$P416[$k];
                                    $Deducciones_4[$i]=$D416[$k];
                                    $Total_4[$i]=$S416[$k];
                                    $Status_4[$i]=$E416[$k];
                                    $Fecha_4[$i]=$F416[$k];
                                }
                            }//Fin for k
                        }else{  
                           // echo "NUMERO ".$Num6." NUMERO";
                                    $Percepciones_4[$i]=0;
                                    $Deducciones_4[$i]=0;
                                    $Total_4[$i]=0;
                                    $Status_4[$i]=0;
                                    $Fecha_4[$i]=0;
                        }//fin else 610
                     }//fin del if compara organismos
                }//fin del for 416

            }else if($Num4>$NumX){//fin del if 416>610
                for ($j=0; $j <$Num4 ; $j++) { 
                    if($ORG6[$i]==$ORG4[$j]){
                        //echo "Percepciones 416 ".$P416[$j]."Deducciones 416 ".$D416[$j].$ORG4[$j]." I <br>";
                        $Percepciones_4[$i]=$P416[$j];
                        $Deducciones_4[$i]=$D416[$j];
                        $Total_4[$i]=$S416[$j];
                        $Status_4[$i]=$E416[$j];
                        $Fecha_4[$i]=$F416[$j];
                        if($NumX>0){
                            for ($k=0; $k <$NumX ; $k++) { 
                                if($ORG4[$j]==$ORGX[$k]){
                                    //echo "Percepciones X00 ".$PX00[$k]."Deducciones X00 ".$DX00[$k].$ORGX[$k]." E <br>";
                                    $Percepciones_X[$i]=$PX00[$k];
                                    $Deducciones_X[$i]=$DX00[$k];
                                    $Total_x[$i]=$SX00[$k];
                                    $Status_x[$i]=$EX00[$k];
                                    $Fecha_x[$i]=$FX00[$k];
                                    //echo $Deducciones_4[$i].$Percepciones_4[$i];
                                }//fin del if compara organismos en 610 y 416
                            }//fin del for del 416
                        }else{
                                    $Percepciones_X[$i]="0";
                                    $Deducciones_X[$i]="0";
                                    $Total_x[$i]="0";
                                    $Status_x[$i]="0";
                                    $Fecha_x[$i]="0";
                                    //echo $Deducciones_4[$i].$Percepciones_4[$i];

                        }//fin del esle 416=0
                    }//fin del if compara organismos X00 y 610
                }
            }//fin del else
            ////////////
            
        }else if($Num4>0){
            for ($j=0; $j <$Num4; $j++) { 
                if($ORGi[$i]==$ORG4[$j]){
                   //echo $P416[$j].$D416[$j];

                }
            }
        }else if($NumX==0&&$Num4==0){
            $Num6=0;
            $Num4=0;
            $Percepciones_X[$i]="0";
            $Percepciones_4[$i]="0";
            $Deducciones_X[$i]="0";
            $Deducciones_4[$i]="0";
            $Total_x[$i]="0";
            $Total_4[$i]="0";
            $Status_x[$i]="0";
            $Status_4[$i]="0";
            $Fecha_x[$i]="0";
            $Fecha_4[$i]="0";
        }//fin del else
    }//fin del for
    for ($i=0; $i <$Num6 ; $i++) { 
        $org=str_replace(" ", "_", $organismos[$i]);
                
                if(isset($Fecha_6[$i])){
                    $fecha6=$Fecha_6[$i];

                }else{
                    $fecha6="0000-00-00";
                }
                if(isset($Fecha_4[$i])){
                    $fecha4=$Fecha_4[$i];
                }else{
                    $fecha4="0000-00-00";
                }
                if(isset($Fecha_x[$i])){
                    $fechax=$Fecha_x[$i];
                }else{
                    $fechax="0000-00-00";
                }

                if(isset($usuarios[$i])){
                    $usuarios[$i]=$usuarios[$i];

                }else{
                    $usuarios[$i]="0";
                }
                
                if(isset($Status_x[$i])){
            if($Status_x[$i]=="T"){
                    $color='label label-success';
                    $tipo='Terminado';
            }else if($Status_x[$i]="A"){
                    $color='label label-primary2';
                    $tipo='Actualizado';
            }
        }elseif (isset($Status_4[$i])) {
          if($Status_4[$i]=="T"){
                    $color='label label-success';
                    $tipo='Terminado';
            }else if($Status_4[$i]="A"){
                    $color='label label-primary2';
                    $tipo='Actualizado';
            }
        }elseif (isset($Status_6[$i])) {
          if($Status_6[$i]=="T"){
                    $color='label label-success';
                    $tipo='Terminado';
            }else if($Status_6[$i]="A"){
                    $color='label label-primary2';
                    $tipo='Actualizado';
            }
        }
echo $tabla= "
  <table class=\"table table-hover\">
       <tbody>
                                    <tr>
                                        <td class=\"project-status\"width=\"50\">
                                            <span class=\"$color\">$tipo</span>
                                        </td>
                                        <td class=\"project-title\"width=\"130\">
                                            <a href=\"organismo=".$usuarios[$i]."&estado=".$org."\" id=\"organismo$i\">";if(isset($organismos[$i])){echo$organismos[$i];}else{echo "Nada";}echo"</a>
                                            <br>
                                            <small>Act.";echo fechas($fechax,$fecha4,$fecha6);echo"</small>
                                        </td>
                                        
                                        
                                        <td class=\"project-completion\" width=\"130\">
                                          <strong>416$ ";if(isset($Total_4[$i])){echo $Total_4[$i];}else{echo "0";} echo "</strong>
                                          <div>   
                                              <small> Perc.: $";if(isset($Percepciones_4[$i])){echo $Percepciones_4[$i];}else{echo "0";} echo"</small><br>
                                              <small> Dedu.: $";if(isset($Deducciones_4[$i])){echo $Deducciones_4[$i];}else{echo "0";} echo"</small>
                                          </div>
                                        </td>

                                      

                                        <td class=\"project-completion\" width=\"130\">
                                              <strong> X00 $";if(isset($Total_x[$i])){echo $Total_x[$i];}else{echo "0";}echo" </strong>
                                                 <div>   
                                                <small> Perc.: $";if(isset($Percepciones_X[$i])){echo $Percepciones_X[$i];}else{echo "0";}echo" </small><br>
                                              <small> Dedu.: $"; if(isset($Deducciones_X[$i])){echo $Deducciones_X[$i];}else{echo "0";}echo" </small>
                                                </div>
                                        </td>
                                        <td class=\"project-completion\" width=\"130\">
                                              <strong> 610 $";if(isset($Total_6[$i])){echo $Total_6[$i];}else{echo "0";}echo"</strong>
                                             <div>   
                                                 <small> Perc.: $"; if(isset($Percepciones_6[$i])){echo $Percepciones_6[$i];}else{echo "0";}echo" </small><br>
                                              <small> Dedu.: $"; if(isset($Deducciones_6[$i])){echo $Deducciones_6[$i];}else{echo "0";}echo" </small>
                                             </div>
                                        </td>
                                        <td class=\"project-people\"width=\"170\">
                                              <a id=\"view-pdf1\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf2\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>

                                              <a id=\"view-pdf3\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.jpg\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>
                                        </td>
                                        <td class=\"project-actions\" width=\"100\">
                                            <a id=\"timeline\" href=\"ptfma_timeline.php?id=".$org."\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x \"></i></a>
                                        </td>
                                    </tr>
                                    
                                    </tbody>
                                </table>";        

}//fin del for que termina la tabla
echo "<div class=\"numero_mayor\" id='$Num6'></div>";//este div es para el scrip que manda a traer ptfma_envia_remesa_info.php

}//fin del ultimo if comprador
        
} // fin de fncIntegraTablaResumen



function fncBuildJSAdmin()
{
return "
			    <!-- Mainly scripts -->
    <script src=\"../js/jquery-2.1.1.js\"></script>
    <script src=\"../js/jquery.js\"></script>
    <script src=\"../js/bootstrap.min.js\"></script>
    <script src=\"../js/plugins/metisMenu/jquery.metisMenu.js\"></script>
    <script src=\"../js/plugins/slimscroll/jquery.slimscroll.min.js\"></script>

    <!-- Flot -->
    <script src=\"../js/plugins/flot/jquery.flot.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.tooltip.min.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.spline.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.resize.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.pie.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.symbol.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.time.js\"></script>

    <!-- Peity -->
    <script src=\"../js/plugins/peity/jquery.peity.min.js\"></script>
    <script src=\"../js/demo/peity-demo.js\"></script>

    <!-- Custom and plugin javascript -->
    <script src=\"../js/inspinia.js\"></script>
    <script src=\"../js/plugins/pace/pace.min.js\"></script>

    <!-- jQuery UI -->
    <script src=\"../js/plugins/jquery-ui/jquery-ui.min.js\"></script>

    <!-- Jvectormap -->
    <script src=\"../js/plugins/jvectormap/jquery-jvectormap-2.0.2.min.js\"></script>
    <script src=\"../js/plugins/jvectormap/jquery-jvectormap-world-mill-en.js\"></script>

    <!-- EayPIE -->
    <script src=\"../js/plugins/easypiechart/jquery.easypiechart.js\"></script>

    <!-- Sparkline -->
    <script src=\"../js/plugins/sparkline/jquery.sparkline.min.js\"></script>

    <!-- Sparkline demo data  -->
    <script src=\"../js/demo/sparkline-demo.js\"></script>

    <script src=\"../js/fileinput.min.js\" type=\"text/javascript\"></script>
    <script src=\"../js/bootstrap.min.js\"></script>
    <script src=\"../js/bootstrapValidator.min.js\"></script>


    <script>
        $(document).ready(function() {
            $('.chart').easyPieChart({
                barColor: '#f8ac59',
//                scaleColor: false,
                scaleLength: 5,
                lineWidth: 4,
                size: 80
            });

            $('.chart2').easyPieChart({
                barColor: '#1c84c6',
//                scaleColor: false,
                scaleLength: 5,
                lineWidth: 4,
                size: 80
            });

            var data2 = [
                [gd(2012, 1, 1), 7], [gd(2012, 1, 2), 6], [gd(2012, 1, 3), 4], [gd(2012, 1, 4), 8],
                [gd(2012, 1, 5), 9], [gd(2012, 1, 6), 7], [gd(2012, 1, 7), 5], [gd(2012, 1, 8), 4],
                [gd(2012, 1, 9), 7], [gd(2012, 1, 10), 8], [gd(2012, 1, 11), 9], [gd(2012, 1, 12), 6],
                [gd(2012, 1, 13), 4], [gd(2012, 1, 14), 5], [gd(2012, 1, 15), 11], [gd(2012, 1, 16), 8],
                [gd(2012, 1, 17), 8], [gd(2012, 1, 18), 11], [gd(2012, 1, 19), 11], [gd(2012, 1, 20), 6],
                [gd(2012, 1, 21), 6], [gd(2012, 1, 22), 8], [gd(2012, 1, 23), 11], [gd(2012, 1, 24), 13],
                [gd(2012, 1, 25), 7], [gd(2012, 1, 26), 9], [gd(2012, 1, 27), 9], [gd(2012, 1, 28), 8],
                [gd(2012, 1, 29), 5], [gd(2012, 1, 30), 8], [gd(2012, 1, 31), 25]
            ];

            var data3 = [
                [gd(2012, 1, 1), 800], [gd(2012, 1, 2), 500], [gd(2012, 1, 3), 600], [gd(2012, 1, 4), 700],
                [gd(2012, 1, 5), 500], [gd(2012, 1, 6), 456], [gd(2012, 1, 7), 800], [gd(2012, 1, 8), 589],
                [gd(2012, 1, 9), 467], [gd(2012, 1, 10), 876], [gd(2012, 1, 11), 689], [gd(2012, 1, 12), 700],
                [gd(2012, 1, 13), 500], [gd(2012, 1, 14), 600], [gd(2012, 1, 15), 700], [gd(2012, 1, 16), 786],
                [gd(2012, 1, 17), 345], [gd(2012, 1, 18), 888], [gd(2012, 1, 19), 888], [gd(2012, 1, 20), 888],
                [gd(2012, 1, 21), 987], [gd(2012, 1, 22), 444], [gd(2012, 1, 23), 999], [gd(2012, 1, 24), 567],
                [gd(2012, 1, 25), 786], [gd(2012, 1, 26), 666], [gd(2012, 1, 27), 888], [gd(2012, 1, 28), 900],
                [gd(2012, 1, 29), 178], [gd(2012, 1, 30), 555], [gd(2012, 1, 31), 993]
            ];


            var dataset = [
                {
                    label: \"Number of orders\",
                    data: data3,
                    color: \"#1ab394\",
                    bars: {
                        show: true,
                        align: \"center\",
                        barWidth: 24 * 60 * 60 * 600,
                        lineWidth:0
                    }

                }, {
                    label: \"Payments\",
                    data: data2,
                    yaxis: 2,
                    color: \"#1C84C6\",
                    lines: {
                        lineWidth:1,
                            show: true,
                            fill: true,
                        fillColor: {
                            colors: [{
                                opacity: 0.2
                            }, {
                                opacity: 0.4
                            }]
                        }
                    },
                    splines: {
                        show: false,
                        tension: 0.6,
                        lineWidth: 1,
                        fill: 0.1
                    },
                }
            ];


            var options = {
                xaxis: {
                    mode: \"time\",
                    tickSize: [3, \"day\"],
                    tickLength: 0,
                    axisLabel: \"Date\",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Arial',
                    axisLabelPadding: 10,
                    color: \"#d5d5d5\"
                },
                yaxes: [{
                    position: \"left\",
                    max: 1070,
                    color: \"#d5d5d5\",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Arial',
                    axisLabelPadding: 3
                }, {
                    position: \"right\",
                    clolor: \"#d5d5d5\",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: ' Arial',
                    axisLabelPadding: 67
                }
                ],
                legend: {
                    noColumns: 1,
                    labelBoxBorderColor: \"#000000\",
                    position: \"nw\"
                },
                grid: {
                    hoverable: false,
                    borderWidth: 0
                }
            };

            function gd(year, month, day) {
                return new Date(year, month - 1, day).getTime();
            }

            var previousPoint = null, previousLabel = null;

            $.plot($(\"#flot-dashboard-chart\"), dataset, options);

            var mapData = {
                \"US\": 298,
                \"SA\": 200,
                \"DE\": 220,
                \"FR\": 540,
                \"CN\": 120,
                \"AU\": 760,
                \"BR\": 550,
                \"IN\": 200,
                \"GB\": 120,
            };




            $('#world-map').vectorMap({
                map: 'world_mill_en',
                backgroundColor: \"transparent\",
                regionStyle: {
                    initial: {
                        fill: '#e4e4e4',
                        \"fill-opacity\": 0.9,
                        stroke: 'none',
                        \"stroke-width\": 0,
                        \"stroke-opacity\": 0
                    }
                },

                series: {
                    regions: [{
                        values: mapData,
                        scale: [\"#1ab394\", \"#22d6b1\"],
                        normalizeFunction: 'polynomial'
                    }]
                },
            });
        });
    </script>
    
 
<script>

(function(a){a.createModal=function(b){defaults={title:\"\",message:\"Your Message Goes Here!\",closeButton:true,scrollable:false};var b=a.extend({},defaults,b);var c=(b.scrollable===true)?'style=\"max-height: 420px;overflow-y: auto;\"':\"\";html='<div class=\"modal fade\" id=\"myModal\">';html+='<div class=\"modal-dialog\">';html+='<div class=\"modal-content\">';html+='<div class=\"modal-header\">';html+='<button type=\"button\" class=\"close\" data-dismiss=\"modal\" aria-hidden=\"true\">×</button>';if(b.title.length>0){html+='<h4 class=\"modal-title\">'+b.title+\"</h4>\"}html+=\"</div>\";html+='<div class=\"modal-body\" '+c+\">\";html+=b.message;html+=\"</div>\";html+='<div class=\"modal-footer\">';if(b.closeButton===true){html+='<button type=\"button\" class=\"btn btn-primary\" data-dismiss=\"modal\">Cerrar</button>'}html+=\"</div>\";html+=\"</div>\";html+=\"</div>\";html+=\"</div>\";a(\"body\").prepend(html);a(\"#myModal\").modal().on(\"hidden.bs.modal\",function(){a(this).remove()})}})(jQuery);

 $('a').on('click',function(event){
 	   // alert('lanza pdf');
        var nombreHref =$(this).attr('id');
        var patt = new RegExp(\"view-pdf\");
        var tm = new RegExp(\"timeline\");

        //alert(nombreHref);
        var pdf_link = $(this).attr('href');
        //alert(pdf_link);
        if (patt.test(nombreHref))
        {  
              
              var iframe = '<div class=\"iframe-container\"><h1> Resultado </h1><iframe src=\"'+pdf_link+'\"></iframe></div>'
              $.createModal({
              title:'Dirección General de Recursos Humanos',
              message: iframe,
              closeButton:true,
              scrollable:false
              });
        }
        else if(tm.test(nombreHref)){
            //alert('timeline');
           $(\"#tablamain\").load(pdf_link);
        }  
        else {
          //alert('Carga total');
           //ESTE REDIRECCIONA A LA MISMA PAGINA window.location.href = \"ptfma_admin.php\";

        }


        return false;        
    });    

</script>
<script>
    $(function(){
        var est=$('.Estados_terminados').attr('id');
        $('#E_Termin').html(est);
        //alert(est);
    });
    </script>
<script>
    $(function(){

        $('a').click(function(){
      var IdQna = event.target.id;
      
                    if(IdQna == 'Qhis')
                     {   
                    //alert('antes');
                    var varhtml ='?'+ $('#Qhis').attr('href');
                    alert(varhtml);
                    
                    $('#main_page').load( \"ptfma_historico_admin.php\"+ varhtml);

                    return false;
                  }else if(IdQna == \"listas\")
                     {   
                    window.location.href=\"ptfma_admin.php\";
                  return false;
                  } 
                  
                  //Obtiene el numero de filas de la tabla y manda un GET con la quincena,anio y organismo para
                  //mostrar la tabla con barras de navegacion del archivo ptfma_envia_remesa_info.php
                  //numero_maximo es la variable que tiene el numero de filas de la tabla

                  var numero_maximo=$(\".numero_mayor\").attr(\"id\");
                    
                      for (var i=0; i <numero_maximo; i++) { 
                        var posicion=i.toString();
                        var organismo='organismo'+posicion;
                        if(IdQna==organismo){
                          var varhtml =$('#Qhis').attr('href');
                          var org ='?'+varhtml+'&'+$('#'+organismo).attr('href');
                          alert(org);
                          $('#main_page').load( \"ptfma_envia_remesa_info.php\"+org);
                        }
                      }
                  //aqui termina el llamado al ptfma_envia_remesa_info.php

        
      }
    );
    });
  </script>

<style type=\"text/css\">
        .iframe-container {    
		    padding-bottom: 60%;
		    padding-top: 30px; height: 0; overflow: hidden;
		}
 
.iframe-container iframe,
.iframe-container object,
.iframe-container embed {
	position: absolute;
	top: 0;
	left: 0;
	width: 100%;
	height: 100%;
}
    </style>		";


} // fin de fncBuildJSAdmin()



function fncBuildBodyAdmin($Qna,$Anio,$fecha_limite,$QnaMax)
{
$db = new DbCnnx(); 

$Listas= ConstruyeListas($Anio,$Qna,$QnaMax);

$SQL_Nominas_General="SELECT 
(SELECT SUM(percepciones)+SUM(deducciones) as Total 
FROM log_carga inner join remesas on log_carga.id_remesas=remesas.id
WHERE numero_periodos=$Qna and anio_periodos=$Anio AND ur='X00')as SX00,
(SELECT SUM(percepciones)+SUM(deducciones) as Total 
FROM log_carga inner join remesas on log_carga.id_remesas=remesas.id
WHERE numero_periodos=$Qna and anio_periodos=$Anio AND ur='610')as S610,
(SELECT SUM(percepciones)+SUM(deducciones) as Total 
FROM log_carga inner join remesas on log_carga.id_remesas=remesas.id
WHERE numero_periodos=$Qna and anio_periodos=$Anio AND ur='416')as S416
FROM log_carga inner join remesas on log_carga.id_remesas=remesas.id
where id_usuarios='campeche@salud.gob.mx'
group by id_usuarios";

$Rows3=$db->select($SQL_Nominas_General);
$RX00="";
$R416="";
$R610="";
$Contador=CERO;
$O_Terminados="";
    if(!$Rows3){
        echo 'Error en consulta';
    }else{
        if(is_array($Rows3)){
            if(isset($Rows3[0]['SX00'])){
                $RX00=$Rows3[0]['SX00'];
            }else{
                $RX00="0";
            }
            if(isset($Rows3[0]['S610'])){
                $R610=$Rows3[0]['S610'];
            }else{
                $R610="0";
            }
            if(isset($Rows3[0]['S416'])){
                $R416=$Rows3[0]['S416'];
            }else{
                $R416="0";
            }


                
       
       
        }
        $SQL_Terminados="SELECT count(distinct(id_usuarios)) as terminados FROM remesas WHERE numero_periodos=$Qna AND estatus='T' and (id_archivos=1 or id_archivos=2 or id_archivos=3);";
        $Rows4=$db->select($SQL_Terminados);
        if(!$Rows4){
            echo "Error de Terminados";
        }else{
            if(is_array($Rows4)){
                $O_Terminados=$Rows4[$Contador]['terminados'];
            }
        }
        
    }

echo "
    <table align=\"center\" height=\"60\" style=\"width: 100%\">
  <tbody><tr>
     <td width=\"40%\" align=\"left\"><img src=\"../images/logoSALUD_hoz.png\" width=\"289\" height=\"95\"></td>
     <!--<td width=\"420\" align=\"left\">
     <img src=\"../images/70Salud.jpg\" width=\"375\" height=\"91\" /></td>-->
     <!--<td width=\"683\" align=\"right\">
     <div id=\"dominio\">Recepción Art. 74</div>

     
     </td>  -->  
     <td width=\"60%\" align=\"right\">
             <div class=\"col-lg-11\">
                    <h2> Dirección General de Recursos Humanos
                    
                    </h2>
        </div>

     
     </td>    
  </tr>
</tbody></table>

    <div id=\"wrapper\">
    <nav class=\"navbar-default navbar-static-side\" role=\"navigation\">
        <div class=\"sidebar-collapse\">
            <ul class=\"nav metismenu\" id=\"side-menu\">
                <li class=\"nav-header\">
                    <div class=\"dropdown profile-element\"> <span>
                            <img alt=\"image\" class=\"img-circle\" src=\"../img/profile_small.jpg\" />
                             </span>
                        <a data-toggle=\"dropdown\" class=\"dropdown-toggle\" href=\"#\">
                            <span class=\"clear\"> <span class=\"block m-t-xs\"> <strong class=\"font-bold\">Noe Alvarez Salvador</strong>
                             </span> <span class=\"text-muted text-xs block\">Art Director <b class=\"caret\"></b></span> </span> </a>
                        <ul class=\"dropdown-menu animated fadeInRight m-t-xs\">
                            <li><a href=\"profile.html\">Profile</a></li>
                            <li><a href=\"contacts.html\">Contacts</a></li>
                            <li><a href=\"mailbox.html\">Mailbox</a></li>
                            <li class=\"divider\"></li>
                            <li><a href=\"../index.php\">Logout</a></li>
                        </ul>
                    </div>
                    <div class=\"logo-element\">
                        IN+
                    </div>
                </li>
                <li class=\"active\">
                    <a href=\"index.html\"><i class=\"fa fa-th-large\"></i> <span class=\"nav-label\">Productos de Nómina</span> <span class=\"fa arrow\"></span></a>
                    <ul class=\"nav nav-second-level\">
                        $Listas
                        
                    </ul>
                </li>
                <!--<li>
                    
                    <a href=\"#\"><i class=\"fa fa-bar-chart-o\"></i> <span class=\"nav-label\">Articulo 74</span><span class=\"fa arrow\"></span></a>
                    <ul class=\"nav nav-second-level collapse\">
                        <li><a href=\"https://www.google.com\">nteriores</a></li>
                        <li><a href=\"#ptfma_admin.php\">Quincena 7 </a></li>
                        <li><a href=\"#ptfma_admin.php\">Quincena 8</a></li>
                        <li class=\"active\"><a href=\"#\">Proximos</a></li>
                    </ul>
                </li>!-->
            </ul>

        </div>
    </nav>

        <div id=\"page-wrapper\" class=\"gray-bg\">
        <div class=\"row border-bottom\">
        <nav class=\"navbar navbar-static-top\" role=\"navigation\" style=\"margin-bottom: 0\">
        <div class=\"navbar-header\">
            <a class=\"navbar-minimalize minimalize-styl-2 btn btn-primary \" href=\"#\"><i class=\"fa fa-bars\"></i> </a>
            <form role=\"search\" class=\"navbar-form-custom\" action=\"#\">
                <div class=\"form-group\">
              
                </div>
            </form>
        </div>
            <ul class=\"nav navbar-top-links navbar-right\">



                <li>
                    <span class=\"m-r-sm text-muted welcome-message\">Dirección General de Recursos Humanos</span>
                </li>
                <li class=\"dropdown\">
                    <a class=\"dropdown-toggle count-info\" data-toggle=\"dropdown\" href=\"#\">
                        <i class=\"fa fa-envelope\"></i>  <span class=\"label label-warning2\">16</span>
                    </a>
                    <ul class=\"dropdown-menu dropdown-messages\">



                        <li>
                            <a href=\"#\">
                                <div>
                                    <i class=\"glyphicon glyphicon-time \"></i> 
                                    Inicia perido de recepción
                                    <span class=\"pull-right text-muted small\">Hace 4 min. </span>
                                </div>
                            </a>
                        </li>
                        <li class=\"divider\"></li>
                        <li>
                            <a href=\"#\">
                                <div>
                                    <i class=\"glyphicon glyphicon-alert\">
                                    </i> Inconsistencia en archivos
                                    <span class=\"pull-right text-muted small\">12 minutes ago</span>
                                </div>
                            </a>
                        </li>
                        <li class=\"divider\" style=\" background-color:#D8D8D8\" ></li>
                        <li>
                            <a href=\"#\">
                                <div>
                                    <i class=\"glyphicon glyphicon-ok-sign\">
                                    </i> Quincena 5
                                    <span class=\"pull-right text-muted small\">4 minutes ago</span>
                                </div>
                            </a>
                        </li>
                        <li class=\"divider\"></li>
                        <li>
                            <div class=\"text-center link-block\">
                                <a href=\"#\">
                                    <strong>Todos los Avisos</strong>
                                    <i class=\"fa fa-angle-right\"></i>
                                </a>
                            </div>
                        </li>



                    </ul>
                </li>
                <li class=\"dropdown\">
                    <a class=\"dropdown-toggle count-info\" data-toggle=\"dropdown\" href=\"#\">
                        <i class=\"fa fa-bell\"></i>  <span class=\"label label-primary2\">8</span>
                    </a>
                    <ul class=\"dropdown-menu dropdown-alerts\">
                        <li>
                            <a href=\"#\">
                                <div>
                                    <i class=\"glyphicon glyphicon-time \"></i> 
                                    Inicia perido de recepción
                                    <span class=\"pull-right text-muted small\">Hace 4 min. </span>
                                </div>
                            </a>
                        </li>
                        <li class=\"divider\"></li>
                        <li>
                            <a href=\"#\">
                                <div>
                                    <i class=\"glyphicon glyphicon-alert\">
                                    </i> Inconsistencia en archivos
                                    <span class=\"pull-right text-muted small\">12 minutes ago</span>
                                </div>
                            </a>
                        </li>
                        <li class=\"divider\" style=\" background-color:#D8D8D8\" ></li>
                        <li>
                            <a href=\"#\">
                                <div>
                                    <i class=\"glyphicon glyphicon-ok-sign\">
                                    </i> Quincena 5
                                    <span class=\"pull-right text-muted small\">4 minutes ago</span>
                                </div>
                            </a>
                        </li>
                        <li class=\"divider\"></li>
                        <li>
                            <div class=\"text-center link-block\">
                                <a href=\"#\">
                                    <strong>Todos los Avisos</strong>
                                    <i class=\"fa fa-angle-right\"></i>
                                </a>
                            </div>
                        </li>
            </ul>

        </nav>
        </div>
            <div class=\"wrapper wrapper-content\">
        <div class=\"row\">
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-success pull-right\" style=\"background-color:#1ABF04\";>Completado</span>
                                <h5>Nómina 416</h5>
                            </div>
                            <div class=\"ibox-content\">
                                <h2 class=\"no-margins\">$R416</h2>
                                <div class=\"stat-percent font-bold text-success\">100% 
                                    <i class=\"fa fa-bolt\"></i></div>
                                <small>Empleados</small>
                            </div>
                        </div>
                    </div>
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-warning2-light pull-right\">Pendiente</span>
                                <h5>Nómina X00</h5>
                            </div>
                            <div class=\"ibox-content\">
                                <h2 class=\"no-margins\">$RX00</h2>
                                <div class=\"stat-percent font-bold text-info\">20% <i class=\"fa fa-level-up\"></i></div>
                                <small>Empleados</small>
                            </div>
                        </div>
                    </div>
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-warning2-light pull-right\">Pendiente</span>
                                <h5>Nomina 610</h5>
                            </div>
                            <div class=\"ibox-content\">
                                <h2 class=\"no-margins\">$R610</h2>
                                <div class=\"stat-percent font-bold text-navy\">44% <i class=\"fa fa-level-up\"></i></div>
                                <small>Empleados</small>
                            </div>
                        </div>
                    </div>
                    <div class=\"col-lg-3\">
                           <div class=\"ibox float-e-margins\">
                              <div class=\"ibox-title\">
                                <span class=\"label label-success pull-right\">En proceso</span>
                                <h5>Estados</h5>
                              </div>
                            <div class=\"ibox-content\">
                                <h1 class=\"no-margins\" id='E_Termin'>$O_Terminados</h1>
                                <div class=\"stat-percent font-bold text-info\">78% <i class=\"fa fa-level-up\"></i></div>
                                <small>Terminados</small>
                            </div>
                          </div>
                        </div>
                    </div>
        <div class=\"row\" id='main_page'>
                    <div class=\"col-lg-12\">

                        <div class=\"ibox float-e-margins\">

                            <div class=\"ibox-title\">


                                <h5>Quincena $Qna Resumen de Envios</h5>
                                <div class=\"pull-right\">

                                Fecha Limite de entrega: $fecha_limite
                                </div>

                            </div>


                <div class=\"ibox-content\">
                         <div class=\"row\">

                                <div id=\"tablamain\" class=\"col-lg-12\">";
                                $Tabla = fncIntegraTablaResumen($Qna,$Anio);
                                  echo"
                                </div>

                        </div>
                </div>

            </div>
        </div>
    </div>


        <div class=\"footer\">
            <div class=\"pull-right\">
                10GB of <strong>250GB</strong> Free.
            </div>
            <div>
                <strong>Copyright</strong> Example Company &copy; 2014-2015
            </div>
        </div>
        </div>
        <div id=\"right-sidebar\">
            <div class=\"sidebar-container\">

                <ul class=\"nav nav-tabs navs-3\">

                    <li class=\"active\"><a data-toggle=\"tab\" href=\"#tab-1\">
                        Notes
                    </a></li>
                    <li><a data-toggle=\"tab\" href=\"#tab-2\">
                        Projects
                    </a></li>
                    <li class=\"\"><a data-toggle=\"tab\" href=\"#tab-3\">
                        <i class=\"fa fa-gear\"></i>
                    </a></li>
                </ul>

                <div class=\"tab-content\">


                    <div id=\"tab-1\" class=\"tab-pane active\">

                        <div class=\"sidebar-title\">
                            <h3> <i class=\"fa fa-comments-o\"></i> Latest Notes</h3>
                            <small><i class=\"fa fa-tim\"></i> You have 10 new message.</small>
                        </div>

                        <div>

                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a1.jpg\">

                                        <div class=\"m-t-xs\">
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                        </div>
                                    </div>
                                    <div class=\"media-body\">

                                        There are many variations of passages of Lorem Ipsum available.
                                        <br>
                                        <small class=\"text-muted\">Today 4:21 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a2.jpg\">
                                    </div>
                                    <div class=\"media-body\">
                                        The point of using Lorem Ipsum is that it has a more-or-less normal.
                                        <br>
                                        <small class=\"text-muted\">Yesterday 2:45 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a3.jpg\">

                                        <div class=\"m-t-xs\">
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                        </div>
                                    </div>
                                    <div class=\"media-body\">
                                        Mevolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).
                                        <br>
                                        <small class=\"text-muted\">Yesterday 1:10 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a4.jpg\">
                                    </div>

                                    <div class=\"media-body\">
                                        Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the
                                        <br>
                                        <small class=\"text-muted\">Monday 8:37 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a8.jpg\">
                                    </div>
                                    <div class=\"media-body\">

                                        All the Lorem Ipsum generators on the Internet tend to repeat.
                                        <br>
                                        <small class=\"text-muted\">Today 4:21 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a7.jpg\">
                                    </div>
                                    <div class=\"media-body\">
                                        Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32.
                                        <br>
                                        <small class=\"text-muted\">Yesterday 2:45 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a3.jpg\">

                                        <div class=\"m-t-xs\">
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                        </div>
                                    </div>
                                    <div class=\"media-body\">
                                        The standard chunk of Lorem Ipsum used since the 1500s is reproduced below.
                                        <br>
                                        <small class=\"text-muted\">Yesterday 1:10 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a4.jpg\">
                                    </div>
                                    <div class=\"media-body\">
                                        Uncover many web sites still in their infancy. Various versions have.
                                        <br>
                                        <small class=\"text-muted\">Monday 8:37 pm</small>
                                    </div>
                                </a>
                            </div>
                        </div>

                    </div>

                    <div id=\"tab-2\" class=\"tab-pane\">

                        <div class=\"sidebar-title\">
                            <h3> <i class=\"fa fa-cube\"></i> Latest projects</h3>
                            <small><i class=\"fa fa-tim\"></i> You have 14 projects. 10 not completed.</small>
                        </div>

                        <ul class=\"sidebar-list\">
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Business valuation</h4>
                                    It is a long established fact that a reader will be distracted.

                                    <div class=\"small\">Completion with: 22%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 22%;\" class=\"progress-bar progress-bar-warning\"></div>
                                    </div>
                                    <div class=\"small text-muted m-t-xs\">Project end: 4:00 pm - 12.06.2014</div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Contract with Company </h4>
                                    Many desktop publishing packages and web page editors.

                                    <div class=\"small\">Completion with: 48%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 48%;\" class=\"progress-bar\"></div>
                                    </div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Meeting</h4>
                                    By the readable content of a page when looking at its layout.

                                    <div class=\"small\">Completion with: 14%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 14%;\" class=\"progress-bar progress-bar-info\"></div>
                                    </div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <span class=\"label label-primary2 pull-right\">NEW</span>
                                    <h4>The generated</h4>
                                    <!--<div class=\"small pull-right m-t-xs\">9 hours ago</div>-->
                                    There are many variations of passages of Lorem Ipsum available.
                                    <div class=\"small\">Completion with: 22%</div>
                                    <div class=\"small text-muted m-t-xs\">Project end: 4:00 pm - 12.06.2014</div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Business valuation</h4>
                                    It is a long established fact that a reader will be distracted.

                                    <div class=\"small\">Completion with: 22%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 22%;\" class=\"progress-bar progress-bar-warning\"></div>
                                    </div>
                                    <div class=\"small text-muted m-t-xs\">Project end: 4:00 pm - 12.06.2014</div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Contract with Company </h4>
                                    Many desktop publishing packages and web page editors.

                                    <div class=\"small\">Completion with: 48%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 48%;\" class=\"progress-bar\"></div>
                                    </div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Meeting</h4>
                                    By the readable content of a page when looking at its layout.

                                    <div class=\"small\">Completion with: 14%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 14%;\" class=\"progress-bar progress-bar-info\"></div>
                                    </div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <span class=\"label label-primary2 pull-right\">NEW</span>
                                    <h4>The generated</h4>
                                    <!--<div class=\"small pull-right m-t-xs\">9 hours ago</div>-->
                                    There are many variations of passages of Lorem Ipsum available.
                                    <div class=\"small\">Completion with: 22%</div>
                                    <div class=\"small text-muted m-t-xs\">Project end: 4:00 pm - 12.06.2014</div>
                                </a>
                            </li>

                        </ul>

                    </div>

                    <div id=\"tab-3\" class=\"tab-pane\">

                        <div class=\"sidebar-title\">
                            <h3><i class=\"fa fa-gears\"></i> Settings</h3>
                            <small><i class=\"fa fa-tim\"></i> You have 14 projects. 10 not completed.</small>
                        </div>

                        <div class=\"setings-item\">
                    <span>
                        Show notifications
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example\">
                                    <label class=\"onoffswitch-label\" for=\"example\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Disable Chat
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" checked class=\"onoffswitch-checkbox\" id=\"example2\">
                                    <label class=\"onoffswitch-label\" for=\"example2\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Enable history
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example3\">
                                    <label class=\"onoffswitch-label\" for=\"example3\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Show charts
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example4\">
                                    <label class=\"onoffswitch-label\" for=\"example4\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Offline users
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" checked name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example5\">
                                    <label class=\"onoffswitch-label\" for=\"example5\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Global search
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" checked name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example6\">
                                    <label class=\"onoffswitch-label\" for=\"example6\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Update everyday
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example7\">
                                    <label class=\"onoffswitch-label\" for=\"example7\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>

                        <div class=\"sidebar-content\">
                            <h4>Settings</h4>
                            <div class=\"small\">
                                I belive that. Lorem Ipsum is simply dummy text of the printing and typesetting industry.
                                And typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.
                                Over the years, sometimes by accident, sometimes on purpose (injected humour and the like).
                            </div>
                        </div>

                    </div>
                </div>

            </div>



        </div>
    </div>

	";
 }// fin de fncBuildBodyAdmin()
 
 function fechas($fechaX00,$fecha416,$fecha610){
$fechamax="";
$fecha="";
$fecha4=substr($fecha416, 0,10);
$fechaX=substr($fechaX00, 0,10);
$fecha6=substr($fecha610, 0,10);

if($fecha4>$fecha6){
$fecha=$fecha4;
}elseif($fecha4<$fecha6){
$fecha=$fecha6;
}elseif($fecha4==$fecha6){
$fecha=$fecha4;
}

if($fecha>$fechaX){
$fechamax=$fecha;
}elseif($fecha<$fechaX){
$fechamax=$fechaX;
}elseif($fecha==$fechaX){
$fechamax=$fechaX;
}

return $fechamax;
 }
 function ConstruyeListas($Anio,$Qna,$QnaMax){
      $HdrLista = "<li class=\"active\">
                    <a href=\"quincenaurl=$Qna&anioquincenaurl=$Anio\" id=\"Qhis\">
                        Anteriores 
                    </a>
                     </li>
                 <li class=\"divider\"></li>  ";

//    $TailLista = "<li><a href=\"$Qna\"id=\"Q100\">Próximas 
  //                    <span class=\"label label-primary pull-right\">NEW
    //                  </span></a>
      //              </li> ";                        
        $Contador  = $Qna;
        $BodyLista = "";
        
           $BodyLista.= "<li><a id=\"listas\"href=\"#\" id=\"Q$Contador\">Quincena Actual</a></li>
                          <li class=\"divider\" style=\" background-color:#D8D8D8\"> </li> ";
        
        $MsgconstruyeListaQnas=$HdrLista.$BodyLista;

      return $MsgconstruyeListaQnas;
  }

?>
