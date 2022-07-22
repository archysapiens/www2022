select count(*)
from (select distinct estado, rfc, ur, qnaproc
from BDART742013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur = 'CON') tabla;


create table RFC_ART_74 AS select distinct rfc
from BDART742013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur = 'CON';

SELECT RFC 
FROM RPTE_CONT;


create table RFC_ART_74_CMPLTO AS select  rfc, UR
from BDART742013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur != 'CON'
GROUP BY rfc, UR;

create table RFC_ART_74_416 AS select  rfc, UR
from BD4162013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 
GROUP BY rfc, UR;

select count(*)
from RFC_ART_74_416;

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

