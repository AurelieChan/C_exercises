select distinct name from people
join stars on stars.person_id = people.id
where movie_id in (select movie_id from stars
where person_id = (select id from people where name = "Kevin Bacon" and birth = '1958'))
and name is not "Kevin Bacon";