create database mp3db;
use mp3db;
grant all on mp3db.* to 'mp3db'@'localhost' identified by 'mp3dbpw';
grant all on mp3db.* to mp3db identified by 'mp3dbpw';

drop table FileTagger;
CREATE TABLE FileTagger (
  Artist      varchar(100),
  TrackTitle  varchar(100),
  AlbumTitle  varchar(100),
  TrackNumber    varchar(10),
  Genre         varchar(20),
  Comment          varchar(200),
  Preference     varchar(20),
  Filename       varchar(200),
  PRIMARY KEY(Filename),
  INDEX(Preference),
  INDEX(Genre)
);



