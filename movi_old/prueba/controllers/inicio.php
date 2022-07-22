<?php
session_start();
if(isset($_SESSION['sesionUsuario']) & @$_COOKIE['id']!=''){
$sufijo='../'; $sufijoMenu='';
require('../bd/bd.php');
include("../template/menu.php");
include("../helpers.php");
include("login/control_session.php");

 ?>
	
		<!DOCTYPE html>
		<html lang="en">
			<head>
				<meta charset="utf-8">
				<meta http-equiv="X-UA-Compatible" content="IE=edge">
				<meta name="viewport" content="width=device-width, initial-scale=1.0">
				<meta name="description" content="">
				<meta name="author" content="">

				<!-- This file has been downloaded from Bootsnipp.com. Enjoy! -->
				<title>Servicios Ecosheys</title>
					<link href="<?=@$sufijo?>web/css/bootstrap.min.css" rel="stylesheet">
					<link href="<?=@$sufijo?>web/font-awesome/css/font-awesome.css" rel="stylesheet">
					<!-- Toastr style -->
					<link href="<?=@$sufijo?>web/css/plugins/toastr/toastr.min.css" rel="stylesheet">
					<link href="<?=@$sufijo?>web/css/animate.css" rel="stylesheet">
					<link href="<?=@$sufijo?>web/css/style.css" rel="stylesheet">
					<link rel="icon" type="image/x-icon" href="<?=@$sufijo?>ico-echosheys.ico">
					<script type="text/javascript" src="<?=@$sufijo?>web/js/HelperJs/scripts/jquery-ui-1-11-2/jquery-1.11.2.js"></script>
			</head>
			<body> <?php

				$loadCssHeader='';	

				$breadcrumb='Inicio';
				$breadcrumbPrincipal='';
				$variables= array('sufijo'=>$sufijo,'sufijoMenu'=>$sufijoMenu,'breadcrumb'=>$breadcrumb,'breadcrumbPrincipal'=>$breadcrumbPrincipal,'loadCssHeader'=>$loadCssHeader);

				/*nombre del archivo a llamar y manda las variables*/
				view('inicio',$variables);?>
		
			<?php top_scroll(); ?>
			<!-- Mainly scripts -->
			<script src="<?=@$sufijo?>web/js/jquery-2.1.1.js"></script>			
			<script src="<?=@$sufijo?>web/js/plugins/jquery-ui/jquery-ui.min.js"></script>
			<script src="<?=@$sufijo?>web/js/bootstrap.min.js"></script>
			<script src="<?=@$sufijo?>web/js/plugins/metisMenu/jquery.metisMenu.js"></script>
			<script src="<?=@$sufijo?>web/js/plugins/slimscroll/jquery.slimscroll.min.js"></script>
			<script src="<?=@$sufijo?>web/js/plugins/select2/select2.js"></script>
			<!-- Modal 
				<script src="web/js/plugins/modal/jquery.modal.js"></script> -->
			<!-- Flot -->
			<script src="<?=@$sufijo?>web/js/plugins/flot/jquery.flot.js"></script>
			<script src="<?=@$sufijo?>web/js/plugins/flot/jquery.flot.tooltip.min.js"></script>
			<script src="<?=@$sufijo?>web/js/plugins/flot/jquery.flot.spline.js"></script>
			<script src="<?=@$sufijo?>web/js/plugins/flot/jquery.flot.resize.js"></script>
			<script src="<?=@$sufijo?>web/js/plugins/flot/jquery.flot.pie.js"></script>
			<!-- Peity -->
			<script src="<?=@$sufijo?>web/js/plugins/peity/jquery.peity.min.js"></script>
			<!-- Custom and plugin javascript -->
			<script src="<?=@$sufijo?>web/js/inspinia.js"></script>
			<script src="<?=@$sufijo?>web/js/plugins/pace/pace.min.js"></script>
			<!-- Toastr -->
			<script src="<?=@$sufijo?>web/js/plugins/toastr/toastr.min.js"></script>
			<script src="<?=@$sufijo?>web/js/apps.js"></script>
			
			<!-- REQUIRED: Functional Widgets -->
			<script src="<?=@$sufijo?>web/js/plugins/smartwidgets/include/jarvis.widget.min.js"></script>


			<script>
				 $(document).ready(function() {
					App.init();
				});
			</script>
<?php

}
else{
    session_unset();
    echo"<script> location.href = '../' </script>";
}
?>
