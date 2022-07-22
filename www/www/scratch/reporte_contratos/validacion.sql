--- proceso de validacion de

select qnaenvio, count(*)
from EMPL_ART_74
where ANIOENV =2013 or ANIOENV ='2013'
group by qnaenvio
order by 1;

select qnaenvio, count(*)
from (
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742013 bd
where bd.qnaenvio >= '16' and bd.qnaenvio >= 16 and  bd.ANIOENV=2013 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV) tabla
group by qnaenvio;

-- 2014
select qnaenvio, count(*)
from EMPL_ART_74
where ANIOENV =2014 or ANIOENV ='2014'
group by qnaenvio
order by 1;

select qnaenvio, count(*)
from (
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742014 bd
where   bd.ANIOENV=2014 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV) tabla
group by qnaenvio
order by 1;


-- 2015

select qnaenvio, count(*)
from EMPL_ART_74
where ANIOENV =2015 or ANIOENV ='2015'
group by qnaenvio
order by 1;

select qnaenvio, count(*)
from (
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742015 bd
where   bd.ANIOENV=2015 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV) tabla
group by qnaenvio
order by 1;

-- 2016 

select qnaenvio, count(*)
from EMPL_ART_74
where ANIOENV =2016 or ANIOENV ='2016'
group by qnaenvio
order by 1;

select qnaenvio, count(*)
from (
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742016 bd
where   bd.ANIOENV=2016 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV) tabla
group by qnaenvio
order by 1;

