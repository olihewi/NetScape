//
// Created by hewis on 10/05/2021.
//
#include <ASGEGameLib/GameObjects/Player/Weapons/WeaponData.h>
WeaponData::WeaponData(nlohmann::json j) :
  weapon_name(j["weapon_name"].get<std::string>()),
  sprite_held(j["sprite_held"].get<std::string>()),
  sprite_floor(j["sprite_floor"].get<std::string>()),
  sprite_ammo(j["sprite_ammo"].get<std::string>()), sfx_fire(j["sfx_fire"].get<std::string>()),
  sfx_reload(j["sfx_reload"].get<std::string>()), sfx_empty(j["sfx_empty"].get<std::string>()),
  sfx_pickup(j["sfx_pickup"].get<std::string>()), is_automatic(j["is_automatic"].get<bool>()),
  damage(j["damage"].get<float>()), max_ammo(j["max_ammo"].get<int>()),
  ammo_reserve(j["ammo_reserve"].get<int>()), fire_rate(j["fire_rate"].get<float>()),
  reload_time(j["reload_time"].get<float>()), recoil(j["recoil"].get<float>()),
  recoil_regain(j["recoil_regain"].get<float>()), inaccuracy(j["inaccuracy"].get<float>()),
  look_distance(j["look_distance"].get<float>()), range(j["range"].get<float>()),
  range_falloff(j["range_falloff"].get<float>()), fire_frames(j["fire_frames"].get<size_t>()),
  reload_frames(j["reload_frames"].get<size_t>())
{
}
nlohmann::json WeaponData::toJson()
{
  nlohmann::json j;
  j["weapon_name"]   = weapon_name;
  j["sprite_held"]   = sprite_held;
  j["sprite_floor"]  = sprite_floor;
  j["sprite_ammo"]   = sprite_ammo;
  j["sfx_fire"]      = sfx_fire;
  j["sfx_reload"]    = sfx_reload;
  j["sfx_empty"]     = sfx_empty;
  j["sfx_pickup"]    = sfx_pickup;
  j["is_automatic"]  = is_automatic;
  j["damage"]        = damage;
  j["max_ammo"]      = max_ammo;
  j["ammo_reserve"]  = ammo_reserve;
  j["fire_rate"]     = fire_rate;
  j["reload_time"]   = reload_time;
  j["recoil"]        = recoil;
  j["recoil_regain"] = recoil_regain;
  j["inaccuracy"]    = inaccuracy;
  j["look_distance"] = look_distance;
  j["range"]         = range;
  j["range_falloff"] = range_falloff;
  j["fire_frames"]   = fire_frames;
  j["reload_frames"] = reload_frames;
  return j;
}
