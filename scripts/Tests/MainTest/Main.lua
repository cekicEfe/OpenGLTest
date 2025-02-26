
local test1 = vec3.new(9,8,6)

print(test1.x)
print(test1.y)
print(test1.z)

local ent = GameEntity.new()
local ent_vec = ent:getPos();

print(ent_vec.x)
print(ent_vec.y)
print(ent_vec.z)
