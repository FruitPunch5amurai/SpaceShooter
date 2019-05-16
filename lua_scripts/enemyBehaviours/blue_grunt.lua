function Update(self,player)
	self:SetVelocity(-self:GetMaxSpeed(),0)
	Attack(self,player)
end
function Attack(self,target)
	--self:FireEnemyProjectile("Animation/PlayerProjectile.json","NormalShot",2,target:GetPosition())	
end