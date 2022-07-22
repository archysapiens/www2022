<?php


/*********************************************************************
 * 
 * Funcion : construyeTablaComentario
 * Objetivo: Construye 
 *           la 3er Tab donde se ingresara un comentario y subira un archivo ya sea 
 *           pdf o imagen para solicitar reactivacion de la quincena para subir su informacion de nomina
 *********************************************************************/
function construyeTablaComentario($TagEnvio,$IdRemesa){

return "

<p>   tagenvio         -   idremesa</p>
<br>

<p>   $TagEnvio             $IdRemesa     </p>




<link href=\"../css/fileinput.css\" media=\"all\" rel=\"stylesheet\" type=\"text/css\" />

<link href=\"../css/bootstrap.min.css\" rel=\"stylesheet\">
<link href=\"../css/style.css\" rel=\"stylesheet\">    
    
    <script src=\"../js/bootstrapValidator.min.js\"></script>
    <script src=\"../js/fileinput.min.js\" type=\"text/javascript\"></script>

  <script type='text/javascript'>
    $(function(){
      
        $('#validacion').bootstrapValidator({
          fields:{
            
            comentario:{
              validators:{
                notEmpty:{
                  message:'Favor de llenar este campo'
                }
              }
            },
            
            archivo:{
              validators:{
                notEmpty:{
                  message:'Favor de seleccionar un archivo'
                }
              }
            }

          }
        });
    }); 
  </script>

<script>
  $(function(){
    $('#texto').hide();
      $('#mostrar').click(function(){
        $('#texto').show(1000);
      });
      $('#ocultar').click(function(){
        $('#texto').hide(1000);
      });
  });
  
</script>
<br>
  <input type=\"radio\" name=\"tipo_attach\" id=\"ocultar\"checked> Deshabilitar<br>
    <input type=\"radio\" name=\"tipo_attach\"  id=\"mostrar\" > Habilitar<br>

     <center> 
     <br>
     <div id='texto' >
     <div class=\"form-group\">





<form action=\"ptfma_subirarchivo.php\" method='post' id='validacion' class=\"form-group\" enctype=\"multipart/form-data\"  >
<div class='form-group' >
      <label for=\"\" class=\"control-label container\">Comentario</label>
    <textarea  style=\"overflow:auto;resize:none\" minlength=\"50\" name=\"comentario\" id=\"comentario\" rows=\"6\" cols=\"95\" class='form-control' placeholder='Escribe tu comentario'></textarea>
    </div>
    <div class='form-group' class=\"control-label\">
      <label for=\"\">Archivo</label>



<input type=\"hidden\" name=\"hidden1\" value=\"$TagEnvio\" ><br><!-- TAGENVIO  -->

<input type=\"hidden\" name=\"hidden2\" value=\"$IdRemesa\" ><br><!--  IDREMESA -->


<style>
  .file-preview-image {
    height: 30px;
    vertical-align: text-center;
}

.file-preview-frame {
    display: table;
    margin: 8px;
    height: 10px;
    border: 1px solid #ddd;
    box-shadow: 1px 1px 5px 0px #a2958a;
    padding: 6px;
    float: left;
    text-align: center;
}
.file-preview-other {
    display: table-cell;
    width: 0px;
    height: 30px;
    font-family: Monaco, Consolas, monospace;
    font-size: 11px;
    vertical-align: middle;
    text-align: center;
}

</style>

<!--  -->
<input type=\"file\" name=\"archivo[]\" multiple=\"true\"  multiple=\"multiple form-data\" multiple data-show-upload=\"false\"
      data-show-caption=\"true\" data-show-remove=\"true\" accept=\"image/png, image/jpeg, image/jpg, application/pdf\" value=\"presiona\" required class=\"file file-loading\" data-allowed-file-extensions='[\"pdf\", \"jpg\", \"jpeg\", \"png\"]'   data-show-preview=\"true\">  


    </div><br>
    <div class=\"form-group\">
      <input type=\"submit\" name=\"boton\" id=\"Enviar_Comentario\" class=\"btn btn-success btn-outline\" value=\"Enviar Comentario\"> 
    </div>
</form> 

  </div>
     </div>";
}


/*********************************************************************
 * 
 * Funcion : cierraRemesa
 * Objetivo: Cierre de remesa y envio a Carag Tabla Staging
 * Parametros
 * $IdRemesa   : Identificador de remesa
 *               
 * Retorno
 * $Resultado  : CERO OK otro Nk
  **********************************************************************/

function cierraRemesa($IdRemesa,$AnioEnvio, $QnaEnvio){
$Resultado=-UNO;
//$TagEnvio = "$QnaEnvio|$AnioEnvio";
$TagEnvio = "$AnioEnvio-$QnaEnvio";
//echo "cierraRemesa/para IdRemesa>$IdRemesa< AnioEnvio>$AnioEnvio< QnaEnvio>$QnaEnvio< <br>";
//echo "cierraRemesa/para TagEnvio>$TagEnvio<<br>";
$db = new DbCnnx();     
if($IdRemesa > CERO){
    $SQL= " update remesas 
            set estatus='T', fecha_actualizacion=now(),
            tag_envio='$TagEnvio' 
            WHERE id = $IdRemesa ";    

    $Rows = $db->select($SQL);    
    echo ">>>".$db->error()."<< <br>";
    $Resultado=CERO;
}
else
    echo "ptfma_envia_remesa_info.inc/cierraRemesa/error($IdRemesa , $AnioEnvio , $QnaEnvio)";
return $Resultado;
} // fin de cierraRemesa

/*********************************************************************
 * 
 * Funcion : construyeTablaProductosNominaUR
 * Objetivo: Construye tabla de los productos de nomina categorizados
 *           por UR
 * Parametros
 * $TagEnvio :  Identificador Tag de Envio de remesa
 * $IdRemesa   : Identificador de remesa
 *               
 * Retorno
 * $Resultado  : Tabla construida
  **********************************************************************/
function construyeTablaProductosNominaUR($TagEnvio,$IdRemesa){

global $TablaRemesaURDetalle;

$HeaderTablaUR="<table class=\"table table-striped table-bordered table-hover dataTables-example dataTable\" id=\"DataTables_Table_0\" aria-describedby=\"DataTables_Table_0_info\" role=\"grid\">
                <thead>
                
                  <tr role=\"row\">
                  <th class=\"sorting\" tabindex=\"0\" aria-controls=\"DataTables_Table_0\" rowspan=\"1\" colspan=\"1\" aria-label=\"Rendering engine: activate to sort column ascending\" style=\"width: 156.889px;\">UR</th>


                  <th class=\"sorting\" tabindex=\"0\" aria-controls=\"DataTables_Table_0\" rowspan=\"1\" colspan=\"1\" aria-label=\"Rendering engine: activate to sort column ascending\" style=\"width: 156.889px;\">Percepcion</th>

                  <th class=\"sorting\" tabindex=\"0\" aria-controls=\"DataTables_Table_0\" rowspan=\"1\" colspan=\"1\" aria-label=\"Rendering engine: activate to sort column ascending\" style=\"width: 156.889px;\">Deduccion</th>


                  <th class=\"sorting\" tabindex=\"0\" aria-controls=\"DataTables_Table_0\" rowspan=\"1\" colspan=\"1\" aria-label=\"Rendering engine: activate to sort column ascending\" style=\"width: 156.889px;\">TotalUR</th>


                 </tr>
                </thead> <tbody>" ;


                                         
$TailTablaUR=" </tbody>      </table>";
$BodyUR="";

$HeadURPN=" <div id=\"company-1\" class=\"tab-pane\">";
$BodyURPN="";
$TAILURPN=" </div>";

$LadoIzq ="";

$db = new DbOracle("test_db", "ArchiSoft");
$dbPN = new DbOracle("test_db", "ArchiSoft");

$sql = "select ur,count(*), sum(percepcion_tot), 
to_char(sum(percepcion),'L999G999G999D99MI') as percepcion, 
to_char(sum(deduccion), 'L999G999G999D99MI') as deduccion, 
to_char((sum(percepcion)-sum(deduccion)), 'L999G999G999D99MI') as total
from (
    select bd.QNAPROC, bd.ur, 
        (select sum (importe) from bdat bt where bd.llave=bt.llave and bt.tconcep='1' and bd.QNAPROC='18' and bd.ANIOPROC='2016' and
          bd.estado='02') as percepcion,  
      (select count(*) from bdat bt where bd.llave=bt.llave and bt.tconcep='1' and bd.QNAPROC='18' and bd.ANIOPROC='2016' and
      bd.estado='02') as percepcion_tot,
    (select sum (importe) from bdat bt where bd.llave=bt.llave and bt.tconcep='2' and bd.QNAPROC='18' and bd.ANIOPROC='2016' and
      bd.estado='02') as deduccion
from bdac bd
where bd.QNAPROC='18' and bd.ANIOPROC='2016' and
bd.estado='02') resultado
group by ur";

$res = $db->execFetchAll($sql, "Query Example");
$contador=1;
$TotalUR=0;
foreach ($res as $row) {
            //  echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";
              $UR=$row['UR'];
              $Percepcion=$row['PERCEPCION'];
              $Deduccion=$row['DEDUCCION'];
              $TotalUR= $row['TOTAL'];
              $BodyUR .= "     <tr>
                <td  ><a data-toggle=\"tab\" href=\"#company-$contador\" class=\"client-link\" aria-expanded=\"false\">$UR</a></td>
                <td align=\"right\">$Percepcion</td>
                <td align=\"right\"><i class=\"fa fa-usd\"></i> $Deduccion</td>
                <td align=\"right\"> $TotalUR </td>
                 </tr> ";


              $SQLPN="select cu.descripcion, bd.tipnom, count(*) AS TOTAL
                      from bdac bd, cat_ur cu 
                      where bd.ur=cu.ur and
                      bd.ur='416'
                      group by cu.descripcion, bd.tipnom
                      order by 1";   

              $ProductoNomina = $dbPN->execFetchAll($SQLPN, "Query Example");    
              $ContadorPN=0;

              foreach ($ProductoNomina as $PN) {

                $Descripcion =$PN['DESCRIPCION'];
                $TipoNomina =$PN['TIPNOM'];
                $TotalRegistros =$PN['TOTAL'];

                if($ContadorPN==CERO){
                          $BodyURPN.="
                                    <div class=\"m-b-lg\">
                                            <h2>$Descripcion</h2>
                                            <p>
                                                Detalle de Productos de nomina
                                            </p>
                                            <div class=\"ibox-tools\">
                                            <span class=\"label label-warning-light pull-right\">10 Messages</span>
                                           </div>
                                   </div>";

                   $HeadTableInner=" <div class=\"client-detail\">
                                    <table class=\"table table-hover no-margins\">
                                            <thead>
                                            <tr>
                                                <th>Producto Nomina</th>
                                                <th>Registros</th>
                                            </tr>
                                            </thead>
                                            <tbody>";                

                    $BodyTableInner="";                          
                    $TailTableInner="  </tbody>
                                        </table>";                

                }else{
                    $BodyTableInner.=" <tr>
                                          <td><span class=\"label label-primary\">
                                              $TipoNomina NAS</span> 
                                          </td>
                                          <td>$TotalRegistros</td>
                                       </tr>  ";      
                }// fin if

                
                $ContadorPN++;
              } 
              $LadoIzq .= "$BodyURPN  $BodyTableInner $TailTableInner" . " </div>";


              // fin foreach
  $contador++;
 } 
  $LadoDerecho = "$HeaderTablaUR $BodyUR  $TailTablaUR";
  //$ArrayFinal  = array($LadoDerecho, $LadoIzq);
  //return $HeaderTablaUR . $BodyUR . $TailTablaUR;
  $TablaRemesaURDetalle = $LadoIzq;
  return $LadoDerecho;
}// fin de construyeTablaProductosNominaUR


/*********************************************************************
 * 
 * Funcion : construyeTablaProductosNomina
 * Objetivo: Construye tabla de los productos de nomina a enviar 
 
 * Parametros
 * $TagEnvio :  Identificador Tag de Envio de remesa
 * $IdRemesa   : Identificador de remesa
 *               
 * Retorno
 * $Resultado  : Tabla construida
  **********************************************************************/

function construyeTablaProductosNomina($TagEnvio,$IdRemesa){
$HeaderTabla ="   <table class=\"table table-striped table-hover\">
                                                <tbody>";

$TailTabla = " </tbody>
                                </table>";
$BodyTabla="";                                

$db = new DbCnnx(); 
$SQLProdNom ="SELECT  logg.id_remesas, logg.tipo_archivo,logg.archivo,logg.registros,
logg.observaciones, logg.etiqueta_envio, logg.archivo_error,
logg.registros_error, logg.estatus, logg.id_tipo_nom, 
(SELECT ct.DESCRIPCION FROM cat_tipnom ct WHERE ct.TIPO=logg.id_tipo_nom  COLLATE utf8_spanish_ci )AS tipo_nomina, (SELECT ct.TIPO FROM cat_tipnom ct WHERE ct.TIPO=logg.id_tipo_nom  COLLATE utf8_spanish_ci )AS tipo
              FROM remesas rem, logger logg
              WHERE rem.id=logg.id_remesas AND 
              rem.id=$IdRemesa AND 
              logg.etiqueta_envio='$TagEnvio' 
              ORDER BY logg.fecha_agregacion";

//echo "construyeTablaProductosNomina/ >>$SQLProdNom<<";

$Rows = $db->select($SQLProdNom);

if(is_array($Rows)){
  $Contador= CERO;
  $TagEnvioActual   = "";
  $TagEnvioAnterior = "";
  $ListaArchivoProdNomina="";

  while(isset($Rows[$Contador]['etiqueta_envio'])) {

      $TagEnvioActual   = $Rows[$Contador]['etiqueta_envio'];
      $IdRemesa         =$Rows[$Contador]['id_remesas'];
      $TipoArchivo      =$Rows[$Contador]['tipo_archivo'];
      $ArchivoProcesado = $Rows[$Contador]['archivo'];
      $NumRegistros     = $Rows[$Contador]['registros'];
      $Observaciones    = $Rows[$Contador]['observaciones'];
      $TipoNomina       = utf8_encode($Rows[$Contador]['tipo_nomina'] );
      $Tipo       = $Rows[$Contador]['tipo'];  

      
      $TipoNominaAux =" ".SUBSTR($TipoNomina,0,7);  

      $ArrNombreArchivoProcesado =explode("/", $ArchivoProcesado);
      $NombreArchivoProcesado =$ArrNombreArchivoProcesado[DOS];


      if($TipoArchivo=='D'){
	      $BodyTabla.="    <tr>
                    <td>
                    <i class=\"fa fa-file-o\" aria-hidden=\"true\" style=\"color:#313131;\"></i>
                    <strong>$NombreArchivoProcesado </strong></td>

                    <td class=\"btn-outline\" style=\"width: 116px;\" data-toggle=\"tooltip\" data-placement=\"top\" title=\"$TipoNomina\" data-original-title=\"Tooltip on top\">$Tipo $TipoNominaAux</td>

                    <td> $NumRegistros</td>
                    <td> $NumRegistros</td>";
    		$BodyTabla.="   <td> Percepciones</td>
                    <td class=\"client-status\">Deducciones</td>
               </tr>";

      }
      else{
	      $BodyTabla.="    <tr>
				    <td>
				    <i class=\"fa fa-file-text-o\" style=\"color:#313131;\"></i>
				    $NombreArchivoProcesado </td>
                    <td class=\"btn-outline\" style=\"width: 116px;\" data-toggle=\"tooltip\" data-placement=\"down\" title=\"$TipoNomina\" data-original-title=\"Tooltip on top\">$Tipo $TipoNominaAux</td>

				    <td> $NumRegistros</td>
				    <td> $NumRegistros</td>";

      		$BodyTabla.="   <td> $ ###,###.##</td>
                    <td class=\"client-status\">$ ###,###.##</td>
               </tr>";
      }                          
      $Contador++;         
   }//fin while
   return $HeaderTabla . $BodyTabla . $TailTabla;
}// fin del if  


}// fin de construyeTablaProductosNomina

/*********************************************************************
 * 
 * Funcion : construyeInfoEnvioRemesas
 * Objetivo: Construye 
 *           considera archivo de datos y trailer
 * Parametros
 * $IdArchivo:  Identificador del Archivo a eliminar
 * $TagEnvio   : Identificador que etiqueta la remesa
 *               
 * Retorno
 * $Resultado  : CERO si se elimino correctamente
 *               otro numero si existe aun el registro
 **********************************************************************/

function construyeInfoEnvioRemesas($TagEnvio,$FechaLimite,$IdRemesa){

 global $TablaRemesaURDetalle;
 global $QnaEnvio;
 global $AnioEnvio;

$ArrayTagEnvio= explode("-", $TagEnvio);
$AnioProceso = $ArrayTagEnvio[1];
$QnaProceso = $ArrayTagEnvio[2]; 
$HeadRemesa = "<div class=\"row\">
                <div class=\"col-sm-8\">
                    <div class=\"ibox\">
                        <div class=\"ibox-content\">
                            <span class=\"text-muted small pull-right\">Fecha Limite: <i class=\"fa fa-clock-o\"></i> $FechaLimite</span>
                             <div class=\"clients-list forum-item active\">


                            <ul class=\"nav nav-tabs\">
                                <span class=\"pull-right small text-muted\">Partidas de Remesa</span>
                                <li class=\"active\">
                                
                                <a data-toggle=\"tab\" href=\"#tab-1\" class=\"client-link\" aria-expanded=\"true\">
                                <i class=\"fa fa-user-md fa-2x\"></i> Producto de Nómina

                                </a>
                                
                                </li>
                                <li class=\"\"><a data-toggle=\"tab\" href=\"#tab-2\" aria-expanded=\"false\"><i class=\"fa fa-hospital-o fa-2x\"></i> Unidades Responsables</a></li>
                                <li class=\"\"><a data-toggle=\"tab\" href=\"#tab-3\" aria-expanded=\"false\"><i class=\"fa fa-hospital-o fa-2x\"></i> Presupestales</a></li>
                            </ul>
					";

$TailRemesa =   "         
</div>

                       </div>
                    </div>
                </div>
            </div>	" ;

$TablaRemesa   = construyeTablaProductosNomina($TagEnvio,$IdRemesa);
$TablaRemesaUR = construyeTablaProductosNominaUR($TagEnvio,$IdRemesa);
$TablaComentarios =  construyeTablaComentario($TagEnvio,$IdRemesa);
//$TablaComentarios =  "En construccion";

//$TablaRemesaURMaster  = $TablaRemesaUR(0);
//$TablaRemesaURDetalle = $TablaRemesaUR(1);

return  "			$HeadRemesa
                            <div class=\"tab-content\">




                                <div id=\"tab-3\" class=\"tab-pane\">
                                    <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\">

                                    <div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">



                                        <div class=\"table-responsive\">

                                      $TablaComentarios


                                        </div>

                                    </div>
</div></div>

















                                <div id=\"tab-1\" class=\"tab-pane active\">
                                    <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">
                                        <div class=\"table-responsive\">

<!-- Fin d ela tabla de productos de nomina -->
										$TablaRemesa
<!-- Fin d ela tabla de productos de nomina -->


                                        </div>

<div class=\"tab-pane\">                                    
<div class=\"col-lg-3 text-center\" >
<button class=\"btn btn-success btn-outline\" type=\"button\"><i class=\"fa fa-print\"></i>&nbsp;&nbsp;<span class=\"bold\">Imprimir</span></button>
</div>
<div class=\"col-lg-3 text-center\" >
<button class=\"btn btn-success btn-outline\" type=\"button\"><i class=\"fa fa-file-excel-o\"></i>&nbsp;&nbsp;<span class=\"bold\">MS Excel</span></button>
</div>
</div>
                                    </div>
                                    </div>

                                </div>

                                <div id=\"tab-2\" class=\"tab-pane\">
                                    <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">



                                        <div class=\"table-responsive\">

                                      $TablaRemesaUR


                                        </div>

                                    </div>



           




                                    <div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: block; border-radius: 7px; z-index: 99; right: 1px; background: rgb(0, 0, 0);\">
                                    </div>

                                    <div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-index: 90; right: 1px; background: rgb(51, 51, 51);\">
                                    </div>


                                    </div>









                                </div>

                            </div>



                            </div>
                        </div>
                    </div>

               </div>

                <div class=\"col-sm-4\">
                    <div class=\"ibox \">

                        <div class=\"ibox-content\">
                            <div class=\"tab-content\">



                                <div id=\"contact-1\" class=\"tab-pane active\">
                                    <div class=\"row m-b-lg\">
                                        <div class=\"col-lg-4 text-center\" 
                                style=\"padding-right: 5px;\">

                                            <h2>Remesa</h2>

                                            <div class=\"m-b-sm\">

                                            
                                            </div>
                                        </div>
                                        <div class=\"col-lg-8\">

                                        <h2>
                                            <strong>

                                                $IdRemesa

                                            </strong>
                                        </h2>

                                            <p>
                                                
                                            </p>
                                        </div>
                                    </div>
                                    <div class=\"client-detail\">
                                    <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">

                                        <strong>Remesa de Productos de Nómina</strong>

                                        <ul class=\"list-group clear-list\">
                                            <li class=\"list-group-item fist-item\">
                                                <span class=\"pull-right\"> $QnaEnvio </span>
                                                Quincena de Envio
                                            </li>
                                            <li class=\"list-group-item\">
                                                <span class=\"pull-right\"> $AnioEnvio </span>
                                                Anio de Envio
                                            </li>
                                            <li class=\"list-group-item\">
                                                <span class=\"pull-right\"> 
                                                <a href=\"#\" class=\"check-link\">
                                                  <i class=\"fa fa-check-square\"></i>
                                                  </a> </span>
                                                Estatus de Validación
                                            </li>
                                            <li class=\"list-group-item\">
                                                <span class=\"pull-right\"> $QnaProceso </span>
                                                Quincena Proceso
                                            </li>
                                            <li class=\"list-group-item\">
                                                <span class=\"pull-right\"> $AnioProceso </span>
                                                Año Proceso
                                            </li>
                                        </ul>
                                        <strong>Nota</strong>
                                        <p>
                                            La información que Ud. ha ingresdo a la Plataforma de Integración de Productos de Nómina, ha sido analizada aplicando las directivas institucionales de Calidad de Información y no se presenta errores o inconsistencias. 
                                        </p>
                                        <hr>

                                    </div>

                                    </div>
                                    </div>
                                </div>

                                    </div>  </div>
                                </div>
          $TailRemesa ";	
}// fin de function


?>