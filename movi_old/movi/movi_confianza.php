<?php

echo " 
<script>
    $('a').click(function(){
            var IdQna = event.target.id;
            var reg = new RegExp(/^vac-noseusa/);
			var edoCtaCredPlat=new RegExp(/^edoCtaCredPlat/);
			
            console.log( IdQna);

        if( reg.test(IdQna)){
            $('#myModal45 .close').click();
            $.post('movi_formulario.php', { \"id\": 1, \"pzavteid\":123 },
              function(response,status) {
                    //alert(response);
                    var string = response;
               $('#main_page').html(response);
               Noe.close() ;
              }// fin function
            ); // fin post
        }
        if( edoCtaCredPlat.test(IdQna)){
            $('#myModal45 .close').click();
			//$.post('movi_formulario_ip.php', { \"id\": 1, \"pzavteid\":123 },
            $.post('movi_formulario_spc.php', { \"id\": 1, \"pzavteid\":123 },
              function(response,status) {
                    //alert(response);
                    var string = response;
               $('#main_page').html(response);
               Noe.close() ;
              }// fin function
            ); // fin post
        }

        else {
            if(IdQna == 'Qhis') {   
                var varhtml ='?'+ $('#Qhis').attr('href');
                $('#contenido').load( \"ptfma_historico.php\"+ varhtml);
                return false;
              }
       }
    }
	);
</script>
    <div id=\"wrapper\">
                        <div class=\"ibox-content forum-container\">

                            <div class=\"forum-title\">
                                <div class=\"pull-right forum-desc\">
                                    <samll>Enablers : 4</samll>
                                </div>
                                <h3>Regulatory Reports</h3>
                            </div>

                            <div class=\"forum-item active\">
                                <div class=\"row\">
                                    <div class=\"col-md-8\">
                                        <div class=\"forum-icon\">
                                            <i class=\"fa fa-credit-card\"></i>
                                        </div>
                                        <a href=\"#\" id=\"vac-noseusa\" class=\"forum-item-title\">Estado de Cuenta Credito Oro</a>
                                        <div class=\"forum-sub-title\">Regulatory Report ID:12-100-1-M1C031P-0000064 </div>
                                    </div>
                                    <div class=\"col-md-4 forum-info\">
                                        <span class=\"views-number\">
                                            RW-075
                                        </span>
                                        <div>
                                            <small>Code ID</small>
                                        </div>
                                    </div>
                                </div>
                            </div>

                            <div class=\"forum-item\">
                                <div class=\"row\">
                                    <div class=\"col-md-8\">
                                        <div class=\"forum-icon\">
                                            <i class=\"fa fa-credit-card\"></i>
                                        </div>
                                        <a href=\"#\" id=\"edoCtaCredPlat\" class=\"forum-item-title\">Estado de Cuenta Credito Platinium</a>
                                        <div class=\"forum-sub-title\">Regulatory Report ID: 12-100-1-M1C019P-0000067  </div>
                                    </div>
                                    <div class=\"col-md-4 forum-info\">
                                        <span class=\"views-number\">
                                             RW-076

                                        </span>
                                        <div>
                                            <small>Codigo</small>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <div class=\"forum-item active\">
                                <div class=\"row\">
                                    <div class=\"col-md-8\">
                                        <div class=\"forum-icon\">
                                            <i class=\"fa fa-credit-card\"></i>
                                        </div>
                                        <a href=\"#\" id=\"vac-noseusa2\" class=\"forum-item-title\">Estado de Cuenta Credito Premier</a>
                                        <div class=\"forum-sub-title\">Regulatory Report ID: 12-100-1-M1C017P-0000071 </div>
                                    </div>
                                    <div class=\"col-md-4 forum-info\">
                                        <span class=\"views-number\">
                                            RW-076
                                        </span>
                                        <div>
                                            <small>Codigo</small>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <div class=\"forum-item\">
                                <div class=\"row\">
                                    <div class=\"col-md-8\">
                                        <div class=\"forum-icon\">
                                            <i class=\"fa fa-credit-card\"></i>
                                        </div>
                                        <a href=\"#\" id=\"vac-noseusa3\" class=\"forum-item-title\">Estado de Cuenta Credito Citibanamex</a>
                                        <div class=\"forum-sub-title\">Regulatory Report ID:  12-100-1-M1C019P-0000078  </div>
                                    </div>
                                    <div class=\"col-md-4 forum-info\">
                                        <span class=\"views-number\">
                                            RW-077
                                        </span>
                                        <div>
                                            <small>Codigo</small>
                                        </div>
                                    </div>
                                </div>
                            </div>





                        </div>
                    </div>
                </div>
            </div>
";

?>