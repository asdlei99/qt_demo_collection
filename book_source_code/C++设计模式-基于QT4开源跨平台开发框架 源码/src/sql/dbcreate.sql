create database mp3db;
use mp3db;
grant all on mp3db.* to 'mp3user'@'localhost' identified by 'mp3dbpw';
grant all on mp3db.* to mp3user identified by 'mp3dbpw';

