--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_Soldiers_C
local WBP_Soldiers = UnLua.Class()

function WBP_Soldiers:Construct()
end

function WBP_Soldiers:InitInfo(SoldierInfo)
    -- œ‘ æ“ªœ¬Õº∆¨
    local imgobj = UE4.LoadObject(img)
    self.BoxImage:SetBrushfromTexture(imgobj)
end


--function WBP_Soldiers:Initialize(Initializer)
--end

--function WBP_Soldiers:PreConstruct(IsDesignTime)
--end

--function WBP_Soldiers:Tick(MyGeometry, InDeltaTime)
--end

return WBP_Soldiers
