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

function WBP_Camps:InitInfo(camp_type)
    self.CampType = camp_type;
end

------------------------- Event -----------------------------

function WBP_Camps:OnClickedCampButton()
    -- ��һ����ǰ��Ӫ��Ϣ�� GS , �Ա����ݵ�ͳ��
    local GS = UE.UGameplayStatics.GetGameState(self);
    GS:SetCurrentCamp(self.CampType);

    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_SelectButton();
    end
end


--function WBP_Camps:Initialize(Initializer)
--end

--function WBP_Camps:PreConstruct(IsDesignTime)
--end

--function WBP_Camps:Tick(MyGeometry, InDeltaTime)
--end

return WBP_Camps
