--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GameData_Solider_C
local WBP_GameData_Solider = UnLua.Class()

function WBP_GameData_Solider:Construct()
    local GS = UE.UGameplayStatics.GetGameState(self);
    GS.OnAINumChange:Add(self,self.RefreshAINum);
end

function WBP_GameData_Solider:InitInfo(CampType, SoliderType)
    self.CampType = CampType;
    self.SoliderType = SoliderType;
    self:RefreshAINum();
end

function WBP_GameData_Solider:RefreshAINum()
    local GS = UE.UGameplayStatics.GetGameState(self);
    local num = GS:GetNumByCampSoliderType(self.CampType, self.SoliderType)
    local str = GS:GetDisplayStrBySoliderType(self.SoliderType)..tostring(num);
    self.SoliderText:SetText(str);
end

--function WBP_GameData_Solider:Initialize(Initializer)
--end

--function WBP_GameData_Solider:PreConstruct(IsDesignTime)
--end

--function WBP_GameData_Solider:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GameData_Solider
