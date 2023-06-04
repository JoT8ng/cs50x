-- Keep a log of any SQL queries you execute as you solve the mystery.

-- CLUES:
-- Took place July 28, 2021
-- Took place on Humphrey Street

-- TODO:
-- Who the thief is
-- What city the thief escaped to
-- Who the thief's accomplice is who helped them escape

-- TIPS:
-- Explore table schemas to understand how tables connect to one another
-- To query across multiple tables, nest queries together or join tables together
-- Maintain a list of suspects


-- START INVESTIGATION:

-- Query crimes to get more data/description of the crime committed
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- New Clues:
-- 10:15am crime
-- Three witness interviews
-- All interview transcripts mentions bakery
-- Littering 16:36

-- Access the three witness interview information
-- Get interviewee names
SELECT DISTINCT name
FROM interviews
WHERE month = 7 AND day = 28;
-- First interview transcript (Jose, Eugene, Barbara, Ruth, Eugene, Raymond, Lily)
SELECT transcript
FROM interviews
WHERE name = 'Eugene' AND month = 7 AND day = 28;
-- Second interview transcript
SELECT transcript
FROM interviews
WHERE name = 'Ruth' AND month = 7 AND day = 28;
-- Third interview transcript
SELECT transcript
FROM interviews
WHERE name = 'Raymond' AND month = 7 AND day = 28;

-- New Clues:
-- 10:15am crime
-- Three witness interviews
-- All interview transcripts mentions bakery
-- Emma's Bakery
-- Thief is someone Eugene recognizes
-- Earlier in morning thief withdrew money from ATM on Leggett Street
-- 10 min after theft thief got into a car in bakery parking lot and drove away (check security footage 10:25)
-- Thief called someone and talked for less than a minute (<60s)
-- Thief planned to take earliest flight next day (29/07)
-- Thief asked accomplice to purchase flight ticket

-- Access Emma's Bakery security log at time and date of crime
-- Check car licence plate
SELECT bakery_security_logs.license_plate, name, bakery_security_logs.activity
FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE activity = 'exit' AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

-- Current Suspects:
-- 5P2BI95 Vanessa
-- 94KL13X Bruce
-- 6P58WS2 Barry
-- 4328GD8 Luca
-- G412CB7 Sofia
-- L93JTIZ Iman
-- 322W7JE Diana
-- 0NTHK55 Kelsey

-- Access ATM Leggett Street information
SELECT atm_transactions.account_number, atm_transactions.transaction_type, atm_transactions.amount, name
FROM people
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE atm_location = 'Leggett Street' AND month = 7 AND day = 28 AND transaction_type = 'withdraw';
-- 28500762 48, Luca
-- 28296815 20, Kenny
-- 76054385 60, Taylor
-- 4961001 50, Bruce
-- 16153065 80, Brooke
-- 25506511 20, Iman
-- 81061156 30, Benista
-- 26013199 35, Diana

-- Current Suspects:
-- Luca
-- Bruce
-- Iman
-- Diana

-- Access information on thief's phonecall to accomplice
SELECT caller, receiver, duration
FROM phone_calls
WHERE month = 7 AND day = 28 AND duration < 60;

SELECT name
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE month = 7 AND day = 28 AND duration < 60
);
-- Kenny, Sofia, Benista, Taylor, Diana, Kelsey Bruce, Carina

-- Current Suspects:
-- Bruce
-- Diana

SELECT name
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE month = 7 AND day = 28 AND duration < 60
);

-- Current Suspects Accomplice:
-- James
-- Larry
-- Anna
-- Jack
-- Melissa
-- Jacqueline
-- Philip
-- Robin
-- Doris

-- Check airports and flights and passengers
-- Find passport number of current suspects
SELECT passport_number
FROM people
WHERE name = 'Bruce';
-- Bruce: 5773159633
-- Diana: 3592750733

-- Find earliest flights out
SELECT origin_airport_id, hour, destination_airport_id
FROM flights
WHERE day = 29 AND month = 7 AND hour < 13;
-- 12AM, origin: 8 (Fiftyville), destination: 11
-- 8AM, origin: 8, destination: 4 (LaGuardia Airport, New York City)
-- 9AM, origin: 8, destination: 1 (O'Hare International Airport, Chicago)

-- Escape Destination Is:
-- New York City

SELECT full_name, city
FROM airports
WHERE id = 4;
-- Find passenger
SELECT flight_id, flights.destination_airport_id, flights.origin_airport_id
FROM passengers
JOIN flights ON flights.id = passengers.flight_id
WHERE passport_number = '5773159633';
-- Bruce: Flight id: 36, origin: fiftyville, destination: New York
-- Diana doesn't match

-- Thief Is:
-- Bruce

-- Determine Accomplice
SELECT phone_number
FROM people
WHERE name = 'Bruce';
-- Bruce phone: (367) 555-5533

SELECT receiver, people.name
FROM phone_calls
JOIN people ON people.phone_number = phone_calls.receiver
WHERE caller = '(367) 555-5533' AND month = 7 AND day = 28 AND duration < 60;

-- Accomplice Is:
-- Robin