select count(*)
from (select distinct estado, rfc, ur, qnaenvio
from BDART742013
where qnaenvio >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur = 'CON') tabla;

drop table EMPL_ART_74;
create table EMPL_ART_74 AS select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742013 bd
where bd.qnaenvio >= '16' and bd.qnaenvio >= 16  and bd.ANIOENV=2013 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742014 bd
where bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and bd.ANIOENV =2014 and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742015 bd
where bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and bd.ANIOENV =2015 and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742016 bd
where bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and bd.ANIOENV =2016 and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV;


select count (*)
from  EMPL_ART_74;

SELECT estado, rfc, ur,CURP, NOMBRE, qnaenvio
FROM EMPL_ART_74
WHERE RFC='POGG740928CH8';

DROP TABLE EMPL_ART_74_CMPLTO;
create table EMPL_ART_74_CMPLTO AS select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742013 bd, EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.qnaenvio >= '16' and bd.qnaenvio >= 16 and bd.ANIOENV =2013 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur != 'CON'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742014 bd, EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2014 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur != 'CON'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742015 bd, EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2015 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur != 'CON'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BDART742016 bd, EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2016 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur != 'CON'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV;


SELECT *
FROM EMPL_ART_74_CMPLTO;

DROP TABLE EMPL_ART_74_416;
create table EMPL_ART_74_416 AS select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BD4162013 bd,EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.qnaenvio >= '16' and bd.qnaenvio >= 16 and bd.ANIOENV =2013 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BD4162014_a bd,EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2014 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BD4162015 bd,EMPL_ART_74 e74
where bd.rfc=e74.rfc and  bd.ANIOENV =2015 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
union all
select  bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV
from BD4162016 bd,EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.ANIOENV =2016 and
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaenvio,bd.ANIOENV;

select count(*)
from EMPL_ART_74_416;

641
2795
3074

select count(*) from reporte_contratos;

drop   table reporte_contratos;
create table reporte_contratos as select rfc,ur,curp,estado, qnaenvio,ANIOENV from bdart742013 where rownum=1;
truncate table reporte_contratos;
select * from reporte_contratos;

insert into  reporte_contratos(rfc,ur) 
SELECT RA74.RFC, RA74C.UR 
FROM RFC_ART_74 RA74 inner  JOIN  RFC_ART_74_CMPLTO RA74C
ON  RA74.RFC=RA74C.RFC
union
SELECT RA74416.RFC, RA74416.UR
FROM RFC_ART_74 RA74 inner  JOIN  RFC_ART_74_416 RA74416
ON  RA74.RFC=RA74416.RFC or substr(RA74.RFC,0,10)=substr(RA74416.RFC,0,10);

select ur, count(*) from reporte_contratos where qnaenvio is not null group by ur;

select substr(rfc,0,10), count(*)
from reporte_contratos
group by substr(rfc,0,10)
having count(*) >1;

select *
from reporte_contratos
where rfc like '%ZANM490823%'

update reporte_contratos rc
set (curp,estado,qnaenvio,ANIOENV) = ( select curp,estado,qnaenvio,ANIOENV from BDART742013 bd
                        where  rc.rfc=bd.rfc and rc.ur=bd.ur and  
                         rownum=1 and  
                        qnaenvio >= '16' and 
                        tipnom='11' and 
                        financiamiento not in (5,6,7,11,13) and
                        funcion !=10 );
                      

update reporte_contratos rc
set (curp,estado,qnaenvio,ANIOENV) = ( select curp,estado,qnaenvio,ANIOENV from BD4162013 bd
                        where  rc.rfc=bd.rfc and rc.ur=bd.ur and  
                         rownum=1 and  
                        qnaenvio >= '16' and 
                        tipnom='11' and 
                        financiamiento not in (5,6,7,11,13) and
                        funcion !=10 )
where qnaenvio is null ; 



select rc.estado, r74.rfc,rc.curp, rc.qnaenvio ,'CON', case rc.ur when 'REG' then rc.ur
                  else null end as REG, case rc.ur when 'HOM' then rc.ur
                  else null end as HOM,
                  case rc.ur when '416' then rc.ur
                  else null end as UR416
from RFC_ART_74 r74 full join  reporte_contratos rc
on  r74.rfc=rc.rfc
where r74.rfc is not null
order by rc.ESTADO, rc.RFC



select *
from bdart742013
where rfc= 'VEGE9303173SA' and
qnaenvio >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur != 'CON';

select *
from bd4162013
where substr(rfc,1,10)= 'VEGE930317' and
qnaenvio >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10;

