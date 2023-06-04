-- Write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0

SELECT DISTINCT name
FROM directors
JOIN people ON directors.person_id = people.id
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE rating >= 9.0;