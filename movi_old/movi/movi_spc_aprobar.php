<?php

date_default_timezone_set('America/Mexico_City');

$Anio = date("Y");

$FechaProcesoTS = date("d-m-Y");
$HoraProcesoTS = date("H:i:s");


echo "
<table class=\"table table-bordered table-condensed table-striped\" style\"\"=\"\"> 
                                                    <tbody><tr> 
                                    <th>Attributos: $Anio </th> 

                                    <th>Attrib Descrition </th> 
                                </tr> 
                                
			<tr> 
				           <td><font size=\"4\">Report Date </font></td> 
				            <td><font size=\"4\"> Date published Account Balance</font></td> 
			</tr> 
			<tr> 
				           <td><font size=\"4\"> RFC
											 </font></td> 
				            <td><font size=\"4\">Federal Taxpayer Registration </font></td> 
			</tr> 
      		 <tr> 
				           <td><font size=\"4\">Estado Origen </font></td> 
				            <td><font size=\"4\">Distrito Federal</font></td> 
			</tr> 
							  <tr> 
                   <td><font size=\"4\">Datos Personales </font></td> 
                    <td><font size=\"4\">Aprobado</font></td> 
                     </tr> 
					 <tr> 

                   <td><font size=\"4\">Datos de Contácto </font></td> 
                    <td><font size=\"4\">Aprobado</font></td> 
                     </tr> 
					 
 	<tr> 
	           <td><font size=\"4\">Documentos</font></td> 
	            <td><font size=\"4\">Aprobados</font></td> 
	             </tr> 
<tr> 
	           <td><font size=\"4\">Codigo Puesto</font></td> 
	            <td><font size=\"4\">Aprobado</font></td> 
	             </tr> 
	<tr> 
	           <td><font size=\"4\">Fecha de Validación </font></td> 
	            <td><font size=\"4\">$FechaProcesoTS $HoraProcesoTS</font></td> 
	             </tr> 
				</tbody></table>

 <form action=\"\" class=\"formName\">
                        <div class=\"form-group\">
                        <label>Comentarios</label>
                        <textarea  type=\"textarea\" cols=\"10\" placeholder=\"Comentarios\" class=\"name form-control\" required />
                        </div>
                        </form>


";



?>