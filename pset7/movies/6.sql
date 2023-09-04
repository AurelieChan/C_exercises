select avg(rating) as average
from ratings
join movies
on movies.id = ratings.movie_id
where year = 2012;