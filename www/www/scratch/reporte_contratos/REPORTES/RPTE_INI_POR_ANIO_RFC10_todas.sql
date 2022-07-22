--Generacionde Reporte de contratos
-- con Innicio de operacione en 2016, 2015, 2014 y 2013

select estado,ce.des_estado, count(*)
from (
select substr(rfc,1,10),estado, min(anioenv||qnaenvio),count(*)
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2016%'
ORDER BY 1,2) tab,  CAT_ESTADOS ce
where tab.estado=ce.ID_ESTADO
group by estado,ce.des_estado
order by estado;

--2015
select estado,ce.des_estado, count(*)
from (
select substr(rfc,1,10),estado, min(anioenv||qnaenvio),count(*)
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2015%'
ORDER BY 1,2) tab,  CAT_ESTADOS ce
where tab.estado=ce.ID_ESTADO
group by estado,ce.des_estado
order by estado;

--2014
select estado,ce.des_estado, count(*)
from (
select substr(rfc,1,10) ,estado, min(anioenv||qnaenvio),count(*)
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2014%'
ORDER BY 1,2) tab,  CAT_ESTADOS ce
where tab.estado=ce.ID_ESTADO
group by estado,ce.des_estado
order by estado;

--2013
select estado,ce.des_estado, count(*)
from (
select substr(rfc,1,10),estado, min(anioenv||qnaenvio),count(*)
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2013%'
ORDER BY 1,2) tab,  CAT_ESTADOS ce
where tab.estado=ce.ID_ESTADO
group by estado,ce.des_estado
order by estado;


--- VALIDACION 2016
--con 2013
select rfcr, tab.estado
from (
select substr(rfc,1,10) as rfcr,estado
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2016%'
ORDER BY 1,2) tab, bdart742013 bd
where tab.estado=bd.estado and tab.rfcr= substr(bd.rfc,1,10)
and bd.ur = 'CON' and 
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and qnaenvio >='16' and anioenv='2013';

-- con 2014
select rfcr, tab.estado
from (
select substr(rfc,1,10) as rfcr,estado
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2016%'
ORDER BY 1,2) tab, bdart742014 bd
where tab.estado=bd.estado and tab.rfcr= substr(bd.rfc,1,10)
and bd.ur = 'CON' and 
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and  anioenv='2014';

-- con 2015
select rfcr, tab.estado
from (
select substr(rfc,1,10) as rfcr,estado
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2016%'
ORDER BY 1,2) tab, bdart742015 bd
where tab.estado=bd.estado and tab.rfcr= substr(bd.rfc,1,10)
and bd.ur = 'CON' and 
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and  anioenv='2015';


-- VALINDANDO 2015
--con 2013
select rfcr, tab.estado
from (
select substr(rfc,1,10) as rfcr,estado
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2015%'
ORDER BY 1,2) tab, bdart742013 bd
where tab.estado=bd.estado and tab.rfcr= substr(bd.rfc,1,10)
and bd.ur = 'CON' and 
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and qnaenvio >='16' and anioenv='2013';

-- con 2014
select rfcr, tab.estado
from (
select substr(rfc,1,10) as rfcr,estado
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2015%'
ORDER BY 1,2) tab, bdart742014 bd
where tab.estado=bd.estado and tab.rfcr= substr(bd.rfc,1,10)
and bd.ur = 'CON' and 
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and  anioenv='2014';


-- VALIDANDO 2014
--con 2013
select rfcr, tab.estado
from (
select substr(rfc,1,10) as rfcr,estado
from reporte_contrato_debug
where UR='CON'
group by substr(rfc,1,10), estado
having min(anioenv||qnaenvio) like '2014%'
ORDER BY 1,2) tab, bdart742013 bd
where tab.estado=bd.estado and tab.rfcr= substr(bd.rfc,1,10)
and bd.ur = 'CON' and 
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and qnaenvio >='16' and anioenv='2013';


--Validando cuadrto
select rfc,estado, min(anioenv||qnaenvio), count(*)
from reporte_contrato_debug
where estado='01' and UR='CON' 
group by rfc, estado
having min(anioenv||qnaenvio) like '2016%'
ORDER BY anioenv||qnaenvio


select rfc, estado, anioenv, qnaenvio, ur
from bdart742013
where rfc='BEBI530802DV7'
and qnaenvio>='16'
order by anioenv, qnaenvio
select count(*) from (
select distinct rfc||estado
from reporte_contrato_debug);

select count(*)
from reporte_contrato_debug;

select substr(rfc,1,10), estado,ur,curp, nombre, qnaenvio,anioenv
from reporte_contrato_debug
order by substr(rfc,1,10), estado, anioenv,qnaenvio;

select count(*)
from (
SELECT rfc, LISTAGG(ur, '-') WITHIN GROUP (ORDER BY anioenv, qnaenvio) 
FROM   reporte_contrato_debug
GROUP BY rfc) tab;

select count(*)
from (select distinct estado||substr(rfc,1,10) from reporte_contrato_debug)tab

