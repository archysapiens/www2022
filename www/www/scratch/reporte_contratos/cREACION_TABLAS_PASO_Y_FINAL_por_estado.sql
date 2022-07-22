drop table EMPL_ART_74;
create table EMPL_ART_74 AS select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742013 bd
where bd.qnaenvio >= '16' and bd.qnaenvio >= 16  and bd.ANIOENV=2013 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON' and bd.estado='25'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742014 bd
where bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and bd.ANIOENV =2014 and
bd.funcion !=10 and bd.ur = 'CON' and bd.estado='25'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742015 bd
where bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and bd.ANIOENV =2015 and
bd.funcion !=10 and bd.ur = 'CON' and bd.estado='25'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742016 bd
where bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and bd.ANIOENV =2016 and
bd.funcion !=10 and bd.ur = 'CON' and bd.estado='25'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV;

DROP TABLE EMPL_ART_74_CMPLTO;
create table EMPL_ART_74_CMPLTO AS select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742013 bd, EMPL_ART_74 e74
where bd.rfc=e74.rfc and (bd.qnaenvio >= '16' or bd.qnaenvio >= 16) and bd.ANIOENV =2013 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur != 'CON' and bd.estado='25'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742014 bd, EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2014 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur != 'CON' and bd.estado='25'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742015 bd, EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2015 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur != 'CON' and bd.estado='25'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742016 bd, EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2016 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur != 'CON' and bd.estado='25'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV;



DROP TABLE EMPL_ART_74_416;
create table EMPL_ART_74_416 AS select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BD4162013 bd,EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.qnaenvio >= '16' and bd.qnaenvio >= 16 and bd.ANIOENV =2013 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10  and bd.estado='25'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BD4162014_a bd,EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2014 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10  and bd.estado='25'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BD4162015 bd,EMPL_ART_74 e74
where bd.rfc=e74.rfc and  bd.ANIOENV =2015 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10  and bd.estado='25'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BD4162016 bd,EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2016 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.estado='25'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV;


drop table reporte_contrato_debug;
create table reporte_contrato_debug as
select * from EMPL_ART_74
union all 
select * from EMPL_ART_74_CMPLTO
union all 
select * from EMPL_ART_74_416;


desc reporte_contrato_debug;
select count(*) from reporte_contrato_debug;

select rfc,estado, ur,CURP,NOMBRE,qnaenvio,anioenv
			from reporte_contrato_debug
			order by rfc,estado,anioenv,qnaenvio;
