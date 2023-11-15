--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_SelectCamp_C
local WBP_SelectCamp = UnLua.Class()

local IsFirstTimes = true;

-- Э��
local function run(self)
    UE.UKismetSystemLibrary.Delay(self, 0.5) -- �ӳ�һ��
    self:Bind()
    self:Init()
end

function WBP_SelectCamp:Construct()
    if(IsFirstTimes) then
        coroutine.resume(coroutine.create(run),self)
        IsFirstTimes = false;
    end
end

function WBP_SelectCamp:Bind()
    self.SelectButton.OnClicked:Add(self, self.OnClickedSelectButton);
    self.ReturnButton.OnClicked:Add(self, self.OnClickedReturnButton);
end

-- ��ʼ��һ����Ӫ
function WBP_SelectCamp:Init()
    local GS = UE.UGameplayStatics.GetGameState(self);
    local CampInfoList = GS:GetCampInfoList();

    for i=1,CampInfoList:Length() do
        local CampSubUIClass = UE.UClass.Load("/Game/Demo/BluePrints/UI/WBP_Camps.WBP_Camps_C")    -- ע��·��
        local CampSubUI = NewObject(CampSubUIClass, self);
        self.CampsList:AddChild(CampSubUI);

        -- ��ʼ��һ�°�ť����ʽ�Լ���Ӫ��Ϣ
        CampSubUI:InitInfo(CampInfoList[i].Type);
    end
end

------------------------------ Event -------------------------------

function WBP_SelectCamp:OnClickedSelectButton()
    if(self.CampsList:IsVisible()) then
        self.CampsList:SetVisibility(UE.ESlateVisibility.Collapsed)
    else
        self.CampsList:SetVisibility(UE.ESlateVisibility.Visible)
    end
end

function WBP_SelectCamp:OnClickedReturnButton()
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_SelectCampReturn();
    end
end

-- function WBP_SelectCamp:PreConstruct(IsDesignTime)
-- end

--function WBP_SelectCamp:Initialize(Initializer)
--end

--function WBP_SelectCamp:Tick(MyGeometry, InDeltaTime)
--end

return WBP_SelectCamp
