<?php
/** INI funciones Humberto **/
function capturaDocumentos(){

return "
<style>
img ssa {
    border: 1px solid #ddd;
    border-radius: 4px;
    padding: 5px;
    width: 150px;
}

img:hover {
    box-shadow: 0 0 2px 1px rgba(0, 140, 186, 0.5);
}
</style>

<script>
$('#EnviarReporte').click(function(){
	
	console.log('se ha enviado el reporte');
	
    var contenido=
            
          '<div>'+
'                                                   <ul class=\"steps\" style=\"margin-left: 0\">'+
'                                                       <li data-step=\"1\" >'+
'                                                           <span class=\"step\">1</span>'+
'                                                           <span class=\"title\">ALS</span>'+
'                                                       </li>'+
''+
'                                                       <li data-step=\"2\" >'+
'                                                           <span class=\"step\">2</span>'+
'                                                           <span class=\"title\">S702</span>'+
'                                                       </li>'+
''+
'                                                       <li data-step=\"3\" >'+
'                                                           <span class=\"step\">3</span>'+
'                                                           <span class=\"title\">C617</span>'+
'                                                       </li>'+
''+
'                                                       <li data-step=\"4\" >'+
'                                                           <span class=\"step\" >4</span>'+
'                                                           <span class=\"title\">S028</span>'+
'                                                       </li>'+
'                                                   </ul>'+
'                                               </div> <hr>'  +
'<p class=\"alert alert-warning \">' +
 '  El proceso tomara unos minutos en cuanto termine recibira una notificacion via email  ' +
  '                                                       </p> '  ;




               $.alert({
                icon: 'fa fa-cog fa-2x fa-fw',
                title: 'Data Tracing Lineage',
                content: contenido,
                columnClass: 'medium',
                animationSpeed:800,
                animationBounce:1,
                animation: 'zoom',
                closeAnimation: 'zoom',
                 animationBounce: 2.5,
                animateFromElement: false,
                theme: 'material',
                type: 'blue',
                buttons: {
                    Aceptar: {
                         btnClass: 'btn-green',
                         action:function () {
                        }
                    }
                }
            });




	

});
</script>

<div id=\"home\" class=\"tab-pane active\">
			<div class=\"row\">
				<div class=\"col-xs-12 col-sm-2 center\">
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>				
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>		
		<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>										
								<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>

					<span class=\"\">

											
<i class=\" ace-icon fa fa-paperclip  big-icon\"></i>



					</span>




				</div><!-- /.col -->

				<div class=\"col-xs-12 col-sm-10\">
					<h4 class=\"blue\">
						<span class=\"middle\"> </span>

						<span class=\"label label-info arrowed-in-right\">
							<i class=\"ace-icon fa fa-circle smaller-80 align-middle\"></i>
							Data Tracing  Process
						</span>
					</h4>

					<div class=\"profile-user-info\">

					<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Regulatory Report</div>
						
													
												
	 <input id=\"archivo-1\" name=\"documentos\" type=\"file\" class=\"file\" multiple=true data-preview-file-type=\"any\">

							
							<div class=\"profile-info-value col-xs-6 \">
							<span>

     <div class=\"col-xs-12\">

	 </div>											
								</span>
							</div>
						</div>		
						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Regulatory Report </div>
								<input id=\"archivo-2\" name=\"documentos\" type=\"file\" class=\"file\" multiple=true data-preview-file-type=\"any\">
												
												<div class=\"profile-info-value col-xs-6 \">
													<span>				
<div class=\"col-xs-12\">
							
															</div>											
												</span>
												</div>
											</div>
											
											




						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Regulatory Report </div>
<input id=\"archivo-3\" name=\"documentos\" type=\"file\" class=\"file\" multiple=true data-preview-file-type=\"any\">															</div>											

							<div class=\"profile-info-value col-xs-6 \">
								<span>

     <div class=\"col-xs-12\">
								</span>
							</div>
						</div>
						
						<!---->
<!--						
						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> CV </div>
	 <input id=\"archivo-4\" name=\"documentos\" type=\"file\" class=\"file\" multiple=true data-preview-file-type=\"any\">

							<div class=\"profile-info-value col-xs-6 \">
								<span>

     <div class=\"col-xs-12\">
	 
															</div>											
								</span>
							</div>
						</div>
						
				<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Identificación Oficial</div>
<input id=\"archivo-5\" name=\"documentos\" type=\"file\" class=\"file\" multiple=true data-preview-file-type=\"any\">	 

							<div class=\"profile-info-value col-xs-6 \">
								<span>

     <div class=\"col-xs-12\">
	 </div>											
								</span>
							</div>
						</div>	

	<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Certificado De Estudios</div>
<input id=\"archivo-6\" name=\"documentos\" type=\"file\" class=\"file\" multiple=true data-preview-file-type=\"any\">	 

							<div class=\"profile-info-value col-xs-6 \">
								<span>

     <div class=\"col-xs-12\">
	 </div>											
								</span>
							</div>
						</div>			
<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Comprobante De Domicilio</div>
<input id=\"archivo-7\" name=\"documentos\" type=\"file\" class=\"file\" multiple=true data-preview-file-type=\"any\">

							<div class=\"profile-info-value col-xs-6 \">
								<span>

     <div class=\"col-xs-12\">
	 </div>											
								</span>
							</div>
						</div>							

-->						

						
					</div>

					<div class=\"hr hr-8 dotted\"></div>

					<div class=\"profile-user-info\">


					</div>
				</div><!-- /.col -->
			</div><!-- /.row -->

			<div class=\"space-20\"></div>

		</div>


";
}

/** FIN funciones Humberto **/



function capturaDocumentosold(){

/** Base 
	http://www.ran.salud.gob.mx/movwebopc2/form-elements.html
	
**/

return "
<div id=\"home\" class=\"tab-pane active\">
			<div class=\"row\">
				<div class=\"col-xs-12 col-sm-2 center\">
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>				
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>		
		<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>										
								<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>

					<span class=\"\">

											
<i class=\"ace-icon fa fa-street-view  big-icon\"></i>

					</span>




				</div><!-- /.col -->

				<div class=\"col-xs-12 col-sm-10\">
					<h4 class=\"blue\">
						<span class=\"middle\"> </span>

						<span class=\"label  label-info  arrowed-in-right\">
							<i class=\"ace-icon fa fa-circle smaller-80 align-middle\"></i>
							Data Tracing  Process
						</span>
					</h4>

					<div class=\"profile-user-info\">

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Pais </div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
<div class=\"form-group\">
								<div class=\"col-xs-12\">
								<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-street-view\"></i>
												</span>
												<input type=\"tel\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Pais\" required=\"\" autofocus=\"\">
											</div>
								</div>
														</div>




													</span>
												</div>
											</div>

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Estado </div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					<input type=\"text\" placeholder=\"Teléfono de Oficina\" name=\"txt_nombre\" id=\"txt_nombre\" class=\"form-control text-capitalize\" required=\"\" autofocus=\"\" data-bv-field=\"txt_nombre\">								
													</span>
												</div>
											</div>




						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> C.P. </div>

							<div class=\"profile-info-value col-xs-6 \">
								<span>
<input type=\"text\" placeholder=\"Teléfono Celular\" name=\"txt_nombre\" id=\"txt_nombre\" class=\"form-control text-capitalize\" required=\"\" autofocus=\"\" data-bv-field=\"txt_nombre\">								
								</span>
							</div>
						</div>

						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Colonia </div>

							<div class=\"profile-info-value  col-xs-6 \">
								<span>
								<input type=\"text\" placeholder=\"@twitter\" name=\"txt_localizacion\" id=\"txt_localizacion\" class=\"form-control text-capitalize\" required=\"\" autofocus=\"\" data-bv-field=\"txt_localizacion\">
								</span>
							</div>
						</div>


						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Calle </div>

							<div class=\"profile-info-value  col-xs-6 \">
								<span>
								<input type=\"text\" placeholder=\"@twitter\" name=\"txt_localizacion\" id=\"txt_localizacion\" class=\"form-control text-capitalize\" required=\"\" autofocus=\"\" data-bv-field=\"txt_localizacion\">
								</span>
							</div>
						</div>

						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Numero Interior </div>

							<div class=\"profile-info-value  col-xs-6 \">
								
								<span><input type=\"text\" placeholder=\"\" name=\"txt_edad\" id=\"txt_edad\" class=\"form-control text-capitalize\" required=\"\" autofocus=\"\" data-bv-field=\"txt_edad\">
								</span>
							</div>
						</div>

					</div>

					<div class=\"hr hr-8 dotted\"></div>

					<div class=\"profile-user-info\">


					</div>
				</div><!-- /.col -->
			</div><!-- /.row -->

			<div class=\"space-20\"></div>

		</div>


";

} // fin de capturaDocumentos

function capturaDomicilio(){

return "
<div id=\"home\" class=\"tab-pane active\">
			<div class=\"row\">
				<div class=\"col-xs-12 col-sm-2 center\">
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>				
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>		
		<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>										
								<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>

					<span class=\"\">

											
<i class=\"ace-icon fa fa-street-view  big-icon\"></i>

					</span>




				</div><!-- /.col -->

				<div class=\"col-xs-12 col-sm-10\">
					<h4 class=\"blue\">
						<span class=\"middle\"> </span>

						<span class=\"label  label-info  arrowed-in-right\">
							<i class=\"ace-icon fa fa-circle smaller-80 align-middle\"></i>
							Data Tracing  Process
						</span>
					</h4>

					<div class=\"profile-user-info\">

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Pais </div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-street-view\"></i>
												</span>
												<input type=\"text\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Pais\" required=\"\" autofocus=\"\">
											</div>			
													</span>
												</div>
											</div>

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Estado </div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-street-view\"></i>
												</span>
												<input type=\"text\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Estado\" required=\"\" autofocus=\"\">
											</div>								
													</span>
												</div>
											</div>




						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> C.P. </div>

							<div class=\"profile-info-value col-xs-6 \">
								<span>
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-street-view\"></i>
												</span>
												<input type=\"number\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"C.P.\" required=\"\" autofocus=\"\">
											</div>
								</span>
							</div>
						</div>

						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Colonia </div>

							<div class=\"profile-info-value  col-xs-6 \">
								<span>
								<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-street-view\"></i>
												</span>
												<input type=\"text\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Colonia\" required=\"\" autofocus=\"\">
											</div>
								</span>
							</div>
						</div>


						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Calle </div>

							<div class=\"profile-info-value  col-xs-6 \">
								<span>
								<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-street-view\"></i>
												</span>
												<input type=\"text\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Calle\" required=\"\" autofocus=\"\">
											</div>
								</span>
							</div>
						</div>

						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Numero Interior </div>

							<div class=\"profile-info-value  col-xs-6 \">
								
								<span>
								<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-street-view\"></i>
												</span>
												<input type=\"number\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Numero Interior\" required=\"\" autofocus=\"\">
											</div>
								</span>
							</div>
						</div>

					</div>

					<div class=\"hr hr-8 dotted\"></div>

					<div class=\"profile-user-info\">


					</div>
				</div><!-- /.col -->
			</div><!-- /.row -->

			<div class=\"space-20\"></div>

		</div>

";
} // fin de function capturaDomicilio()



function capturaContacto(){

return "
<div id=\"home\" class=\"tab-pane active\">
			<div class=\"row\">
				<div class=\"col-xs-12 col-sm-2 center\">
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
		<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>										
								<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>

					<span class=\"\">

											
<i class=\"ace-icon fa fa-at big-icon\"></i>

					</span>




				</div><!-- /.col -->

				<div class=\"col-xs-12 col-sm-10\">
					<h4 class=\"blue\">
						<span class=\"middle\"> </span>

						<span class=\"label  label-info  arrowed-in-right\">
							<i class=\"ace-icon fa fa-circle smaller-80 align-middle\"></i>
							Data Tracing  Process
						</span>
					</h4>

					<div class=\"profile-user-info\">

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Email </div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
						<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-at\"></i>
												</span>
												<input type=\"text\" value=\"\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Email\" required=\"\" autofocus=\"\">
											</div>							
													</span>
												</div>
											</div>

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Oficina </div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-phone\"></i>
												</span>
												<input type=\"tel\" value=\"\" id=\"telefono\" name=\"telefono\" class=\"form-control\" placeholder=\"Numero De oficina\" required=\"\" autofocus=\"\">
											</div>					
					</span>
												</div>
											</div>




						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Celular </div>

							<div class=\"profile-info-value col-xs-6 \">
								<span>
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-mobile-phone\"></i>
												</span>
												<input type=\"tel\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Celular\" required=\"\" autofocus=\"\">
											</div>
								</span>
							</div>
						</div>

						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Twitter </div>

							<div class=\"profile-info-value  col-xs-6 \">
								<span>
								<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-tumblr-square\" ></i>
												</span>
												<input type=\"email\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"twitter\" required=\"\" autofocus=\"\">
											</div>
								</span>
							</div>
						</div>

						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Uso Futuro </div>

							<div class=\"profile-info-value  col-xs-6 \">
				<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-facebook-official\"></i>
												</span>
												<input type=\"text\" value=\"\" id=\"telefonoce\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Uso Futuro\" required=\"\" autofocus=\"\">
											</div>				
								
								</span>
							</div>
						</div>

					</div>

					<div class=\"hr hr-8 dotted\"></div>

					<div class=\"profile-user-info\">


					</div>
				</div><!-- /.col -->
			</div><!-- /.row -->

			<div class=\"space-20\"></div>

		</div>

";
} // fin de function capturaContacto()

function capturaPersonales(){

return "<div id=\"home\" class=\"tab-pane active\">
			<div class=\"row\">
				<div class=\"col-xs-12 col-sm-3 center\">
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
					<span class=\"profile-picture\">
						<img class=\"editable img-responsive\" alt=\"Regulatory Report\" id=\"avatar2\" src=\"../images/report.png\" style=\"width: 220px;height:220px;\">
					</span>

					<div class=\"space space-4\"></div>

					<a href=\"#\" class=\"btn btn-sm btn-block btn-success\">
						<i class=\"ace-icon fa fa-plus-circle bigger-120\"></i>
						<span class=\"bigger-110\">RRID:12-100-1-M1C031P-0000064 </span>
					</a>

				</div><!-- /.col -->

				<div class=\"col-xs-12 col-sm-9\">
					<h4 class=\"blue\">
						<span class=\"middle\"> </span>

						<span class=\"label  label-info  arrowed-in-right\">
							<i class=\"ace-icon fa fa-circle smaller-80 align-middle\"></i>
							Data Tracing  Process
						</span>
					</h4>

					<div class=\"profile-user-info\">

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Data Owner </div>

												<div class=\"profile-info-value col-xs-6 \">
													<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-user fa-lg\"></i>
												</span>
												<input type=\"text\" value=\"\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Data Owner SOID\" required=\"\" autofocus=\"\">
											</div>
												</div>
											</div>

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Data Stewards </div>

												<div class=\"profile-info-value col-xs-6 \">
													<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\"blue fa fa-user fa-lg\"></i>
												</span>
												<input type=\"text\" value=\"\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Data Domain Stewards\" required=\"\" autofocus=\"\" >
											</div>
												</div>
											</div>




						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Data Custodian </div>

							<div class=\"profile-info-value col-xs-6 \">
								<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-user fa-lg\"></i>
												</span>
												<input type=\"text\" value=\"\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\" Data Custodian\" required=\"\" autofocus=\"\">
											</div>
							</div>
						</div>


						<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> Date Information </div>

							<div class=\"profile-info-value  col-xs-6 \">
								<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-user fa-lg\"></i>
												</span>
												<input type=\"date\" value=\"\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Fecha De la información\" required=\"\" autofocus=\"\">
											</div>
							</div>
						</div>


					</div>

					<div class=\"hr hr-8 dotted\"></div>

					<div class=\"profile-user-info\">


					</div>
				</div><!-- /.col -->
			</div><!-- /.row -->

			<div class=\"space-20\"></div>

		</div>
";

}// fin de capturaPersonales

$Personales=capturaPersonales();
$Contacto= capturaContacto();
$Domicilio = capturaDomicilio();
$Documentos = capturaDocumentos();

echo "
          
<div class=\"wrapper wrapper-content animated fadeInRight\" id=\"main_page_2\" style=\"
    padding-top: 0px;\">
						<div class=\"row\">
							<div class=\"col-lg-12 \">
								<div class=\"ibox float-e-margins\">
									<div class=\"ibox-title\">
										<h3>RWA - Data Tracing Process Configuration </h3>
									</div>

<!-- inicio formulario -->



							<div class=\"col-xs-12\">
								<!-- PAGE CONTENT BEGINS -->
								<div class=\"tabbable\">
									<ul class=\"nav nav-tabs padding-18 tab-size-bigger\" id=\"myTab\">
										<li class=\"active\">
											<a data-toggle=\"tab\" href=\"#faq-tab-1\">
												<i class=\"blue ace-icon fa fa-cog bigger-220\"></i>
												Configuración
											</a>
										</li>
<!--
										<li>
											<a data-toggle=\"tab\" href=\"#faq-tab-2\">
												<i class=\"blue ace-icon fa  fa-at bigger-220\"></i>
												Contácto
											</a>
										</li>

										<li>
											<a data-toggle=\"tab\" href=\"#faq-tab-3\">
												<i class=\"blue ace-icon fa fa-street-view bigger-220\"></i>
												Domicilio
											</a>
										</li>

-->
										<li>
											<a data-toggle=\"tab\" href=\"#faq-tab-4\">
												<i class=\"blue ace-icon fa fa-paperclip bigger-220\"></i>
												Report
											</a>
										</li>

										<li>
											<a data-toggle=\"tab\" href=\"#faq-tab-5\">
												<i class=\"blue ace-icon fa fa-cogs bigger-220\"></i>
												Data Tracing Process 
											</a>
										</li>

<!--

										<li>
											<a data-toggle=\"tab\" href=\"#faq-tab-6\">
												<i class=\"green ace-icon fa fa-th-list bigger-220\"></i>
												Percepciones
											</a>
										</li>


										<li>
											<a data-toggle=\"tab\" href=\"#faq-tab-7\">
												<i class=\"orange ace-icon fa fa-th-list bigger-220\"></i>
												Deducciones
											</a>
										</li>

-->
									</ul>



									<div class=\"tab-content no-border padding-24\">


										<div id=\"faq-tab-1\" class=\"tab-pane fade in active\">
											<h4 class=\"blue\">
												<i class=\"ace-icon fa fa-check bigger-110\"></i>
												Regulatory Data Tracing Process Configuration
											</h4>

$Personales


											<div class=\"space-8\"></div>

											<div id=\"faq-list-1\" class=\"panel-group accordion-style1 accordion-style2\">

												<div class=\"panel panel-default\">

												</div>

												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>
											</div>
										</div>







										<div id=\"faq-tab-2\" class=\"tab-pane fade\">
											<h4 class=\"blue\">
												<i class=\"blue  ace-icon fa fa-at bigger-110\"></i>
												Información de Contácto
											</h4>
<div class=\"space-8\"></div>

$Contacto


											<div class=\"space-8\"></div>

											<div id=\"faq-list-2\" class=\"panel-group accordion-style1 accordion-style2\">
												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>
											</div>
										</div>





										<div id=\"faq-tab-3\" class=\"tab-pane fade\">
											<h4 class=\"blue\">
												<i class=\"blue ace-icon fa fa-street-view bigger-110\"></i>
												Datos de Domicilio
											</h4>
$Domicilio


											<div class=\"space-8\"></div>

											<div id=\"faq-list-3\" class=\"panel-group accordion-style1 accordion-style2\">
												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>
											</div>
										</div>
										<div id=\"faq-tab-4\" class=\"tab-pane fade\">
											<h4 class=\"blue\">
												<i class=\"blue ace-icon fa fa-paperclip bigger-110\"></i>
												Regulatory Report Account Balance
											</h4>
$Documentos

											<div class=\"space-8\"></div>

											<div id=\"faq-list-4\" class=\"panel-group accordion-style1 accordion-style2\">
												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
													
												</div>

												<div class=\"panel panel-default\">
												</div>
											</div>
										</div>
<!-- fin propuesto-->
							


										<div id=\"faq-tab-5\" class=\"tab-pane fade\">
						<div id=\"faq-tab-5\" class=\"tab-pane fade active in\">
											<h4 class=\"blue\">
												<i class=\"blue ace-icon fa fa-credit-card bigger-110\"></i>
												Data Tracing Automation Process
											</h4>

<div id=\"home\" class=\"tab-pane active\">
			<div class=\"row\">
				<div class=\"col-xs-12 col-sm-2 center\">
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>				
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>		
		<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>										
								<div class=\"space space-4\"></div>
				<div class=\"space space-4\"></div>

					<span class=\"\">

											
<i class=\"ace-icon fa fa-credit-card    big-icon\"></i>

					</span>




				</div><!-- /.col -->

				<div class=\"col-xs-12 col-sm-10\">
					<h4 class=\"blue\">
						<span class=\"middle\"> </span>

						
					</h4>
					

					<div class=\"profile-user-info\">
					
					<div class=\"profile-info-row\">
					
					
					
					
												<div class=\"profile-info-name blue\"> Regulatory Report
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>				
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card\"></i>
												</span>
												<input type=\"text\" value=\"Estado de Cuenta Credito Oro\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Función\" required=\"\" autofocus=\"\"readonly>
											</div>						
												</div>
												
											</div>
					
											<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Regulatory Report
												
</div>

								<div class=\"profile-info-value col-xs-6 \">
													<span>				
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card\"></i>
												</span>
												<input type=\"text\" value=\"12-100-1-M1C019P-0000067-E-G-S\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Función\" required=\"\" autofocus=\"\"readonly>
											</div>						
												</div>
												
											</div>




						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Fecha Informacion
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					

<span class=\"lbl\">
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card\"></i>
												</span>
												<input type=\"text\" value=\"03-Mar-2022\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Sunfunción\" required=\"\" autofocus=\"\" readonly>
											</div>
													




													</span>
												</div>
												
											</div>




						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Data Owner
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					

<span class=\"lbl\">
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card\"></i>
												</span>
												<input type=\"text\" value=\"Juan Lopez Maldonado\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Sunfunción\" required=\"\" autofocus=\"\" readonly>
											</div>
													




													</span>
												</div>
												
											</div>



			<div class=\"profile-info-row\">
							<div class=\"profile-info-name blue\"> 
							</div>

							<div class=\"profile-info-value col-xs-6 \">
										<span>				
											<div class=\"input-group\">
											<!--
												<span class=\"input-group-addon\">
												
													<i class=\" blue fa fa-credit-card\"></i>
												
										</span>
											-->
							<!-- <button class=\"btn btn-primary  dim btn-large-dim\" type=\"button\">
							<i class=\"fa fa-location-arrow\"></i></button>
							-->
							<a id=\"EnviarReporte\" class=\"btn btn-success btn-circle btn-lg\" type=\"button\">
							<i class=\"fa fa-check\"></i>
                            </a>
										
							</div>						
							</div>
							
							<div class=\"profile-info-value col-xs-6 \">
										
									
									
							</div>

												
				</div>
											
<!--
						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Unidad
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					

<span class=\"lbl\">
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card\"></i>
												</span>
												<input type=\"text\" value=\"610\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Sunfunción\" required=\"\" autofocus=\"\" readonly>
											</div>
													




													</span>
												</div>
												
											</div>



						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Partida
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
												<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card\"></i>
												</span>
												<input type=\"text\" value=\"1204\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"Grupo\" required=\"\" autofocus=\"\"readonly>
											</div>
													<span>
					


					


													</span>	
												</div>
												
											</div>

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Puesto
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					


				
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card\"></i>
												</span>
												<input type=\"text\" value=\"CF41075\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"All\" required=\"\" autofocus=\"\"readonly>
											</div>

													</span>

													




													
												</div>
												
											</div>

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Proyecto Programa
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					


					
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card\"></i>
												</span>
												<input type=\"text\" value=\"2\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"PP\" required=\"\" autofocus=\"\"readonly>
											</div>

													</span>

													




													
												</div>
											
											</div>

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Grupo Funcional
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					

					
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card \"></i>
												</span>
												<input type=\"text\" value=\"2\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"UR\" required=\"\" autofocus=\"\" readonly>
											</div>

													</span>
</span>
													




													
												</div>
												
											</div>

						<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Función
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					

					
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card \"></i>
												</span>
												<input type=\"text\" value=\"3\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"UR\" required=\"\" autofocus=\"\"readonly>
											</div>

													</span>
</span>
													




													
												</div>
												
											</div>										


											
														<div class=\"profile-info-row\">
												<div class=\"profile-info-name blue\"> Subfunción
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					

					
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card \"></i>
												</span>
												<input type=\"text\" value=\"03\" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"UR\" required=\"\" autofocus=\"\"readonly>
											</div>

													</span>
</span>
													




													
												</div>
												
											</div>	
					<div class=\"profile-info-row\">
										<div class=\"profile-info-name blue\"> Num Puesto
												
</div>

												<div class=\"profile-info-value col-xs-6 \">
													<span>
					

					
<div class=\"input-group\">
												<span class=\"input-group-addon\">
													<i class=\" blue fa fa-credit-card \"></i>
												</span>
												<input type=\"text\" value=\"5528 \" id=\"inputUsuario\" name=\"inputUsuario\" class=\"form-control\" placeholder=\"UR\" required=\"\" autofocus=\"\"readonly>
											</div>

													</span>
</span>
													




													
												</div>
												
											</div>
											
-->											
											
												<div class=\"profile-info-value col-xs-6 \">
													<span>
					

					
<div class=\"input-group\">
												
</span>
													




													
												</div>
												
											</div>											
											

					</div>

					<div class=\"hr hr-8 dotted\"></div>

					<div class=\"profile-user-info\">


					</div>
				</div><!-- /.col -->
			</div><!-- /.row -->

			<div class=\"space-20\"></div>

		</div>



											<div class=\"space-8\"></div>

											<div id=\"faq-list-5\" class=\"panel-group accordion-style1 accordion-style2\">
												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>

												<div class=\"panel panel-default\">
												</div>
											</div>
										</div>
										</div>
<!-- fin 5 propuesto-->






										<div id=\"faq-tab-6\" class=\"tab-pane fade\">
											<h4 class=\"blue\">
												<i class=\"blue ace-icon fa fa-th-list bigger-110\"></i>
												Conceptos de Percepción
											</h4>

											<div class=\"space-8\"></div>

											<div id=\"faq-list-6\" class=\"panel-group accordion-style1 accordion-style2\">
												<div class=\"panel panel-default\">
													<div class=\"panel-heading\">
														<a href=\"#faq-6-1\" data-parent=\"#faq-list-6\" data-toggle=\"collapse\" class=\"accordion-toggle collapsed\">
															<i class=\"ace-icon fa fa-plus\" data-icon-hide=\"ace-icon fa fa-minus\" data-icon-show=\"ace-icon fa fa-hand-o-right\"></i>
															<span class=\"label label-info arrowed-in-right arrowed\">
															Concepto 1-07-00
															</span>
														</a>
													</div>

													<div class=\"panel-collapse collapse\" id=\"faq-6-1\">
														<div class=\"panel-body\">
															$ 20,000.00 SUELDOS BASE

														</div>
													</div>
												</div>

												<div class=\"panel panel-default\">
													<div class=\"panel-heading\">
														<a href=\"#faq-6-2\" data-parent=\"#faq-list-6\" data-toggle=\"collapse\" class=\"accordion-toggle collapsed\">
															<i class=\"ace-icon fa fa-plus bigger-120\" 
															data-icon-hide=\"ace-icon fa-minus\" data-icon-show=\"ace-icon fa fa-frown-o\"></i>
<span class=\"label label-info arrowed-in-right arrowed\">
															Concepto 1-06-CG
															</span>
														</a>
													</div>

													<div class=\"panel-collapse collapse\" id=\"faq-6-2\">
														<div class=\"panel-body\">
															$ 40,000.00  COMPENSACION GARANTIZADA 

														</div>
													</div>
												</div>

												<div class=\"panel panel-default\">
													<div class=\"panel-heading\">

														<a href=\"#faq-6-3\" data-parent=\"#faq-list-6\" data-toggle=\"collapse\" class=\"accordion-toggle collapsed \">
															<i class=\"ace-icon fa fa-plus smaller-80\" 
															data-icon-hide=\"ace-icon fa fa-minus\" data-icon-show=\"ace-icon fa fa-plus\"></i>
															<span class=\"label label-info arrowed-in-right arrowed\">
															Concepto 1-38-00
															</span>
														</a>
													</div>

													<div class=\"panel-collapse collapse\" id=\"faq-6-3\">
														<div class=\"panel-body\">
$ 2,000.00  AYUDA DE DESPENSA

														</div>
													</div>
												</div>


											</div>
										</div>
<!-- fin 6 propuesto-->








										<div id=\"faq-tab-7\" class=\"tab-pane fade\">
											<h4 class=\"blue\">
												<i class=\"blue ace-icon fa fa-th-list bigger-110\"></i>
												Conceptos de Deducción
											</h4>

											<div class=\"space-8\"></div>

											<div id=\"faq-list-7\" class=\"panel-group accordion-style1 accordion-style2\">
												<div class=\"panel panel-default\">
													<div class=\"panel-heading\">
														<a href=\"#faq-7-1\" data-parent=\"#faq-list-7\" data-toggle=\"collapse\" class=\"accordion-toggle collapsed\">
															<i class=\"ace-icon fa fa-plus\" data-icon-hide=\"ace-icon fa fa-hand-o-down\" data-icon-show=\"ace-icon fa fa-hand-o-right\"></i>
															<span class=\"label label-info arrowed-in-right arrowed\">
															Concepto 2-01-00
															</span>

														</a>
													</div>

													<div class=\"panel-collapse collapse\" id=\"faq-7-1\">
														<div class=\"panel-body\">
IMPUESTO SOBRE LA RENTA


														</div>
													</div>
												</div>

												<div class=\"panel panel-default\">
													<div class=\"panel-heading\">
														<a href=\"#faq-7-2\" data-parent=\"#faq-list-7\" data-toggle=\"collapse\" class=\"accordion-toggle collapsed\">
															<i class=\"ace-icon fa fa-plus bigger-120\" data-icon-hide=\"ace-icon fa fa-smile-o\" data-icon-show=\"ace-icon fa fa-frown-o\"></i>
															<span class=\"label label-info arrowed-in-right arrowed\"> Concepto 2-02-SI</span>

														</a>
													</div>

													<div class=\"panel-collapse collapse\" id=\"faq-7-2\">
														<div class=\"panel-body\">
SEGURO DE INVALIDEZ Y VIDA, ISSSTE


														</div>
													</div>
												</div>

												<div class=\"panel panel-default\">
													<div class=\"panel-heading\">
														<a href=\"#faq-7-3\" data-parent=\"#faq-list-7\" data-toggle=\"collapse\" class=\"accordion-toggle collapsed\">
															<i class=\"ace-icon fa fa-plus smaller-80\" data-icon-hide=\"ace-icon fa fa-minus\" data-icon-show=\"ace-icon fa fa-plus\"></i>
															<span class=\"label label-info arrowed-in-right arrowed\">Concepto 2-02-SR</span>

														</a>
													</div>

													<div class=\"panel-collapse collapse\" id=\"faq-7-3\">
														<div class=\"panel-body\">

SEGURO DE RETIRO, CESANTÍA EN EDAD AVANZADA Y VEJEZ, ISSSTE



														</div>
													</div>
												</div>

												<div class=\"panel panel-default\">
													<div class=\"panel-heading\">
														<a href=\"#faq-7-4\" data-parent=\"#faq-list-7\" data-toggle=\"collapse\" class=\"accordion-toggle collapsed\">
															<i class=\"ace-icon fa fa-plus smaller-80\" data-icon-hide=\"ace-icon fa fa-minus\" data-icon-show=\"ace-icon fa fa-plus\"></i>
															<span class=\"label label-info arrowed-in-right arrowed\">Concepto 2-02-SS</span>

														</a>
													</div>

													<div class=\"panel-collapse collapse\" id=\"faq-7-4\">
														<div class=\"panel-body\">
SERVICIOS SOCIALES Y CULTURALES, ISSSTE


														</div>
													</div>
												</div>
											</div>
										</div>
<!-- fin 7 propuesto-->




									</div>
						





<!-- fin formulario -->
									<div class=\"ibox-content\">
										<div class=\"board\">
											<div class=\"board-inner\">
												<div class=\"tabs-left\"></div>
											</div>



										</div>
									</div>
								</div>
							</div>
						</div>
					</div>
					



<script src=\"../js/bootstrapValidator.min.js\"></script>

 <!-- iCheck -->
    <script src=\"../js/plugins/iCheck/icheck.min.js\"></script>
	
<script>
$(document).ready(function () {

                $('#FormUser').bootstrapValidator({
                    feedbackIcons: {
                        valid: 'glyphicon glyphicon-ok',
                        invalid: 'glyphicon glyphicon-remove',
                        validating: 'glyphicon glyphicon-refresh'
                    },
                    fields: {
                        txt_nombre: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                },
                                regexp: {
                                    regexp: /^[a-zA-Z\s\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+$/,
                                    message: ' '
                                }
                            }
                        },
                        txt_app_p: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                },
                                regexp: {
                                    regexp: /^[a-zA-Z\s\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+$/,
                                    message: ' '
                                }
                            }
                        },
                        txt_app_m: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                },
                                regexp: {
                                    regexp: /^[a-zA-Z\s\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+$/,
                                    message: ' '
                                }
                            }
                        },
                        txt_foto: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                }
                            }
                        },
                        txt_cargo: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                },
                                regexp: {
                                    regexp: /^[a-zA-Z\s\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+$/,
                                    message: ' '
                                }
                            }
                        },
                        txt_email: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                },
                                regexp: {
                                    regexp: /^[a-zA-Z0-9.-_\s]+$/,
                                    message: ' '
                                }
                            }
                        },
                        txt_psw: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                },
                                
                                different: {
                                    field: 'txt_email',
                                    message: 'La contraseña no puede ser la misma que el correo'
                                }
                            }
                        },
                        txt_conf_psw: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                },
                                identical: {
                                    field: 'txt_psw',
                                    message: 'La contraseña y su confirmación no coinciden'
                                },
                                different: {
                                    field: 'txt_email',
                                    message: 'La contraseña no puede ser lo mismo que el correo'
                                }
                            }
                        },
                        txt_organismos: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                }
                            }
                        },
                        txt_uni_respon: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                }
                            }
                        },
                        txt_pregunta_seguridad: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                }
                            }
                        },
                        txt_licencia: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                },
                                regexp: {
                                    regexp: /^[a-zA-Z0-9_\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+$/,
                                    message: 'Error en Número de Licencia '
                                }
                            }
                        },
                        txt_respuesta: {
                            validators: {
                                notEmpty: {
                                    message: ' '
                                },
                                regexp: {
                                    regexp: /^[a-zA-Z\s\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+$/,
                                    message: ' '
                                }
                            }
                        }
                    }
                });

                $('.i-checks').iCheck({
                    checkboxClass: 'icheckbox_square-green',
                    radioClass: 'iradio_square-green',
                });
           

  });
</script>
 <!--<link href=\"http://netdna.bootstrapcdn.com/bootstrap/3.1.0/css/bootstrap.min.css\" rel=\"stylesheet\">-->
<link href=\"../css/fileinput.min.css\" media=\"all\" rel=\"stylesheet\" type=\"text/css\" />
<!---<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js\"></script>-->
<script src=\"../js/fileinput.min.js\" type=\"text/javascript\"></script>
<!-- <link href=\"../css/boopstrap.min.css\" media=\"all\" rel=\"stylesheet\" type=\"text/css\"/>-->




";


?>