--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_HP_C
local WBP_HP = UnLua.Class()

function WBP_HP:Construct()
    self:InitHp()
    self.AI.OnTakeDamage:Add(self, self.RefreshHp)
end

function WBP_HP:InitHp()
    local Percent = self.AI:GetCurrentHp() / self.AI:GetMaxHp();
    self.HP:SetPercent(Percent)

    local Color = self.AI:GetColorByCampType();
    local LinearColor = UE.UKismetMathLibrary.Conv_ColorToLinearColor(Color);
    self.HP:SetFillColorAndOpacity(LinearColor);
end

function WBP_HP:RefreshHp()
    local Percent = self.AI:GetCurrentHp() / self.AI:GetMaxHp();
    self.HP:SetPercent(Percent)
end


--function WBP_HP:Initialize(Initializer)
--end

--function WBP_HP:PreConstruct(IsDesignTime)
--end

--function WBP_HP:Tick(MyGeometry, InDeltaTime)
--end

return WBP_HP
