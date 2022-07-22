select distinct estado, rfc
from BDART742013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur = 'CON' and rfc='AALM601002E61';

select distinct estado, rfc
from BDART742013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10  and rfc='AALM601002E61';
