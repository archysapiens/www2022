select count(*)
from (select distinct estado, rfc, ur, qnaproc
from BDART742013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur = 'CON') tabla;

drop table EMPL_ART_74;
create table EMPL_ART_74 AS select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc
from BDART742013 bd
where bd.qnaproc >= '16' and 
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc
union 
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc
from BDART742014 bd
where bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc
union 
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc
from BDART742015 bd
where bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc
union 
select  bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc
from BDART742016 bd
where bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur = 'CON'
GROUP BY bd.rfc, bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc;


select count (*)
from  EMPL_ART_74;

SELECT estado, rfc, ur,CURP, NOMBRE, qnaproc
FROM EMPL_ART_74
WHERE RFC='POGG740928CH8';

DROP TABLE EMPL_ART_74_CMPLTO;
create table EMPL_ART_74_CMPLTO AS select   bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc
from BDART742013 bd, EMPL_ART_74 e74
where bd.rfc=e74.rfc and bd.qnaproc >= '16' and 
bd.tipnom='11' and 
bd.financiamiento not in (5,6,7,11,13) and
bd.funcion !=10 and bd.ur != 'CON'
GROUP BY bd.rfc,bd.estado, bd.ur,bd.CURP, bd.NOMBRE, bd.qnaproc,bd.anioproc

union
select  estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
from BDART742014
where tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur != 'CON'
GROUP BY estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
union
select  estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
from BDART742015
where tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur != 'CON'
GROUP BY estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
union
select  estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
from BDART742016
where tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur != 'CON'
GROUP BY estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc;


SELECT *
FROM EMPL_ART_74_CMPLTO;
DROP TABLE EMPL_ART_74_416;

create table EMPL_ART_74_416 AS select  estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
from BD4162013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 
GROUP BY estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
union
select  estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
from BD4162014_a
where tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 
GROUP BY estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
union
select  estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
from BD4162015
where tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 
GROUP BY estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
union
select  estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
from BD4162016
where tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 
GROUP BY estado, rfc, ur,CURP, NOMBRE, qnaproc,anioproc
;

select count(*)
from EMPL_ART_74_416;

641
2795
3074

select count(*) from reporte_contratos;

drop   table reporte_contratos;
create table reporte_contratos as select rfc,ur,curp,estado, qnaproc,anioproc from bdart742013 where rownum=1;
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

select ur, count(*) from reporte_contratos where qnaproc is not null group by ur;

select substr(rfc,0,10), count(*)
from reporte_contratos
group by substr(rfc,0,10)
having count(*) >1;

select *
from reporte_contratos
where rfc like '%ZANM490823%'

update reporte_contratos rc
set (curp,estado,qnaproc,anioproc) = ( select curp,estado,qnaproc,anioproc from BDART742013 bd
                        where  rc.rfc=bd.rfc and rc.ur=bd.ur and  
                         rownum=1 and  
                        qnaproc >= '16' and 
                        tipnom='11' and 
                        financiamiento not in (5,6,7,11,13) and
                        funcion !=10 );
                      

update reporte_contratos rc
set (curp,estado,qnaproc,anioproc) = ( select curp,estado,qnaproc,anioproc from BD4162013 bd
                        where  rc.rfc=bd.rfc and rc.ur=bd.ur and  
                         rownum=1 and  
                        qnaproc >= '16' and 
                        tipnom='11' and 
                        financiamiento not in (5,6,7,11,13) and
                        funcion !=10 )
where qnaproc is null ; 



select rc.estado, r74.rfc,rc.curp, rc.qnaproc ,'CON', case rc.ur when 'REG' then rc.ur
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
qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur != 'CON';

select *
from bd4162013
where substr(rfc,1,10)= 'VEGE930317' and
qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10;

