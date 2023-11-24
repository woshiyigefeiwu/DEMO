--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_Camps_C
local WBP_Camps = UnLua.Class()

function WBP_Camps:Construct()
    self:Bind()
end

function WBP_Camps:Bind()
    self.CampButton.OnClicked:Add(self, self.OnClickedCampButton);
end

function WBP_Camps:InitInfo(CampInfo)
    self.CampType = CampInfo.Type;

    -- self.Overridden.InitInfo(self,CampInfo);
    self.SetColor(self,CampInfo);
    self.SetText(self,CampInfo);
end

------------------------- Event -----------------------------

function WBP_Camps:OnClickedCampButton()
    -- 传一个当前阵营信息给 GS , 以便数据的统计
    local GS = UE.UGameplayStatics.GetGameState(self);
    GS:SetCurrentCamp(self.CampType);

    -- local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    -- local MyPC = MyPawn:GetController();
    -- if(MyPC) then
    --     MyPC:OnClick_SelectButton();
    -- end

    local GS = UE.UGameplayStatics.GetGameState(self);
    if(GS and GS:GetUIManager()) then
        local UIM = GS:GetUIManager();
        UIM:ShowUI("UI_PlaceAI");
    end
end


--function WBP_Camps:Initialize(Initializer)
--end

--function WBP_Camps:PreConstruct(IsDesignTime)
--end

--function WBP_Camps:Tick(MyGeometry, InDeltaTime)
--end

return WBP_Camps
